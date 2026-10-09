#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PathPoint {
    VecFx32 pos;
    s32 speed;
    s32 wait;
} PathPoint;

typedef struct PathEntry {
    u32 first : 10;
    u32 count : 10;
    u32 extra : 12;
} PathEntry;

typedef struct PathOwner {
    u8 pad_00[0xb8];
    PathEntry *paths;
    PathPoint *points;
} PathOwner;

typedef struct PathActor {
    u8 pad_00[0xa8];
    VecFx32 pos;
    u8 pad_b4[0x58];
    u8 collision[0x28];
    u8 bounds[0x18];
    u8 pad_14c[4];
    VecFx32 delta;
    u8 sweptBounds[0x18];
} PathActor;

typedef struct PathMover {
    u8 pad_00[4];
    PathOwner *owner;
    u8 pad_08[0x2a];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 pos;
    u8 pad_44[0x2c];
    u16 flags70;
    s16 pathIndex;
    u8 pad_74[0x10];
    VecFx32 collisionPos;
    u8 pad_90[0x10];
    VecFx32 origin;
    u8 pad_ac[0x14];
    u32 flagsC0;
    u8 pad_c4[0x28];
    u16 pointIndex : 15;
    u16 pointFlag : 1;
    u8 pad_ee[2];
    s32 progress;
    s32 timer;
} PathMover;

#define DIVCNT      (*(volatile u16 *)0x04000280)
#define DIV_RESULT  (*(volatile s64 *)0x040002a0)
#define SQRTCNT     (*(volatile u16 *)0x040002b0)
#define SQRT_RESULT (*(volatile u32 *)0x040002b4)

extern const VecFx32 data_02053438;

extern PathActor *func_02036240(u32 id);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void SetCollisionObjectPosition_02033f48(void *object, const VecFx32 *position);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern BOOL CopyEntryValueIfSet_020a2c88(PathMover *mover, PathPoint *point);
extern void func_ov016_020a2558(PathMover *mover);

static inline void CP_SetDiv64_64(u64 numerator, u64 denominator)
{
    DIVCNT = 2;
    *(u64 *)0x04000290 = numerator;
    *(u64 *)0x04000298 = denominator;
}

static inline void CP_SetSqrt64(u64 parameter)
{
    SQRTCNT = 1;
    *(u64 *)0x040002b8 = parameter;
}

void UpdatePathMovement_020a2ca4(PathMover *mover)
{
    VecFx32 delta = {0, 0, 0};
    VecFx32 newPos;
    VecFx32 diff;
    VecFx32 target;
    VecFx32 step;
    PathEntry *paths;
    s32 pathIndex;
    PathActor *actor;
    PathOwner *owner;
    PathPoint *points;
    PathPoint *start;
    PathPoint *current;
    BOOL found;
    PathPoint *next;
    BOOL finished;
    BOOL nonzero;
    BOOL partial;
    s32 index;
    s32 length;
    u32 root;
    s64 lengthSq;
    s64 scale;

    finished = FALSE;
    newPos = mover->pos;
    actor = func_02036240(mover->actorId);
    if (mover->timer > 0) {
        mover->timer -= 0x88;
        if (mover->timer < 0) {
            mover->timer = 0;
        }
        actor->delta = delta;
        OffsetBoxByDelta_0203ac70(actor->bounds, actor->sweptBounds, &actor->delta);
        return;
    }
    found = FALSE;
    pathIndex = mover->pathIndex;
    owner = mover->owner;
    if (pathIndex == -1 || (paths = owner->paths) == NULL || (points = owner->points) == NULL) {
        return;
    }
    if (paths[pathIndex].count <= 1) {
        return;
    }
    start = &points[paths[pathIndex].first];
    mover->flags70 |= 0x20;
    if (!(mover->flagsC0 & 4)) {
        mover->flagsC0 |= 4;
        if (CopyEntryValueIfSet_020a2c88(mover, start)) {
            actor->delta = data_02053438;
            OffsetBoxByDelta_0203ac70(actor->bounds, actor->sweptBounds, &actor->delta);
            return;
        }
    }
    mover->flagsC0 &= ~0x800000;
    do {
        index = mover->pointIndex;
        current = &start[index];
        next = current + 1;
        if (index + 1 >= paths[pathIndex].count) {
            next = NULL;
        }
        if (next == NULL) {
            mover->pointIndex = 0;
            mover->progress = 0;
            CopyEntryValueIfSet_020a2c88(mover, start);
            newPos = mover->origin;
            finished = TRUE;
            mover->flagsC0 |= 0x800000;
        } else if (!found) {
            if (current->speed <= 0) {
                mover->pointIndex = index + 1;
            } else {
                VEC_Subtract_01ff9e3c(&next->pos, &current->pos, &diff);
                nonzero = TRUE;
                partial = TRUE;
                if (diff.x == 0 && diff.y == 0) {
                    partial = FALSE;
                }
                if (!partial && diff.z == 0) {
                    nonzero = FALSE;
                }
                if (nonzero) {
                    lengthSq = (s64)diff.x * diff.x;
                    lengthSq += (s64)diff.y * diff.y;
                    lengthSq += (s64)diff.z * diff.z;
                    CP_SetSqrt64((u64)(lengthSq * 4));
                    CP_SetDiv64_64(0x0100000000000000LL, (u64)lengthSq);
                    mover->progress += (current->speed << 8) / 30;
                    while (SQRTCNT & 0x8000) {
                    }
                    root = SQRT_RESULT;
                    length = (s32)(root + 1) >> 1;
                } else {
                    length = 0;
                }
                if (length == 0 || length < mover->progress / 256) {
                    mover->progress -= length << 8;
                    mover->pointIndex++;
                    if (CopyEntryValueIfSet_020a2c88(mover, next)) {
                        target = next->pos;
                        found = TRUE;
                    }
                } else {
                    while (DIVCNT & 0x8000) {
                    }
                    scale = DIV_RESULT * (s32)root;
                    delta.x = (fx32)((scale * diff.x + 0x100000000000LL) >> 45);
                    delta.y = (fx32)((scale * diff.y + 0x100000000000LL) >> 45);
                    delta.z = (fx32)((scale * diff.z + 0x100000000000LL) >> 45);
                    ScaleVecFx32InPlace_0204a5e4(&delta, mover->progress / 256);
                    VEC_Add_01ff9e0c(&current->pos, &delta, &target);
                    found = TRUE;
                }
                if (found) {
                    VEC_Subtract_01ff9e3c(&mover->origin, &start->pos, &step);
                    VEC_Add_01ff9e0c(&step, &target, &newPos);
                    VEC_Subtract_01ff9e3c(&newPos, &mover->pos, &delta);
                }
            }
        }
    } while (!found && !finished);
    if (finished) {
        VEC_Subtract_01ff9e3c(&mover->origin, &mover->pos, &delta);
    }
    actor->delta = delta;
    OffsetBoxByDelta_0203ac70(actor->bounds, actor->sweptBounds, &actor->delta);
    VEC_Add_01ff9e0c(&mover->pos, &delta, &mover->pos);
    SetCollisionObjectPosition_02033f48(actor->collision, &mover->collisionPos);
    actor->pos = mover->pos;
    func_ov016_020a2558(mover);
}
