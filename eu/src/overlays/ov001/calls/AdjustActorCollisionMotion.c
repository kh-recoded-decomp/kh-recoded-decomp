#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MoveActor {
    u8 reserved000[0x128];
    u8 flags128;
    u8 reserved129[0x26c - 0x129];
    u32 flags26c : 31;
    u32 reserved26c : 1;
    u8 reserved270[0x288 - 0x270];
    u16 stateLow : 2;
    u16 moveKind : 2;
    u16 stateMid : 3;
    u16 blocked : 1;
    u16 stateUpper : 5;
    u16 slide : 1;
    u16 stateHigh : 2;
    u16 reserved28a;
    u16 flagsLow : 14;
    u16 wallMotion : 1;
    u16 hasContact : 1;
    u8 reserved28e[0x29c - 0x28e];
    fx32 maxCorrection;
    u8 reserved2a0[0x2c0 - 0x2a0];
    VecFx32 position;
    u8 reserved2cc[0x38c - 0x2cc];
    VecFx32 correction;
} MoveActor;

typedef struct HitPlane {
    u8 reserved00[0x14];
    s16 normalX, normalY, normalZ;
} HitPlane;

typedef struct HitObject {
    u8 reserved00[0xc];
    u8 flags;
    u8 reserved0d[0x6c - 0xd];
    s32 kind;
} HitObject;

typedef struct CollisionHit {
    u8 reserved00[8];
    HitPlane *plane;
    u8 reserved0c[4];
    HitObject *object;
    u8 reserved14[0x24 - 0x14];
    s32 sortKey;
} CollisionHit;

typedef char MoveActorPositionOffsetCheck[
    (u32)&((MoveActor *)0)->position == 0x2c0 ? 1 : -1];
typedef char MoveActorCorrectionOffsetCheck[
    (u32)&((MoveActor *)0)->correction == 0x38c ? 1 : -1];
typedef char CollisionSortKeyOffsetCheck[
    (u32)&((CollisionHit *)0)->sortKey == 0x24 ? 1 : -1];

extern BOOL func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern void VEC_MultAdd(fx32, const VecFx32 *, const VecFx32 *, VecFx32 *);
extern void VEC_Subtract(const VecFx32 *, const VecFx32 *, VecFx32 *);
extern fx32 VEC_DotProduct(const VecFx32 *, const VecFx32 *);
extern fx32 VEC_Mag(const VecFx32 *);
extern fx32 VEC_NormalizeLength(const VecFx32 *, VecFx32 *);
extern fx32 FX_Div(fx32, fx32);
extern fx32 FX_Mul(fx32, fx32);
extern CollisionHit *SweepActorStep(MoveActor *, const VecFx32 *, const VecFx32 *, VecFx32 *);
extern void ScaleVecFx32InPlace(VecFx32 *, fx32);
extern const VecFx32 gZeroVecFx32;

static inline int GetSessionMode(void)
{
    if (func_ov001_02063a24()) return func_ov001_02063a38();
    return 0;
}

static inline void SetMotionVector(VecFx32 *vector, fx32 x, fx32 y, fx32 z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void AdjustActorCollisionMotion(MoveActor *actor, VecFx32 *position,
                                VecFx32 *motion, const CollisionHit *hit)
{
    VecFx32 normal;
    VecFx32 delta;
    VecFx32 opposite;
    VecFx32 normalized;
    VecFx32 deflection;
    VecFx32 projection;
    VecFx32 step;
    VecFx32 nearEnd;
    VecFx32 farEnd;
    CollisionHit *nearHit;
    fx32 scale;

    if (GetSessionMode() == 7) return;
    if (!hit) {
        if (!actor->hasContact || actor->slide || (actor->flags26c & 0x80)
            || (actor->flags128 & 2)) return;
        position->x = motion->x;
        position->z = motion->z;
        return;
    }
    if (!hit->plane) return;
    if (hit->object) {
        switch (hit->object->kind) {
        case 1:
        case 2:
            if (actor->slide || (actor->flags26c & 0x80)) return;
            break;
        case 23:
            if (actor->moveKind == 1 || (hit->object->flags & 2)) return;
            break;
        case 25:
            if (actor->moveKind == 1 || (hit->object->flags & 2)) return;
            break;
        }
    }
    if (GetSessionMode() == 4) {
        SetMotionVector(&normal, hit->plane->normalX, 0, hit->plane->normalZ);
        VEC_MultAdd(0x29, &normal, motion, motion);
        position->x = motion->x;
        position->z = motion->z;
        return;
    }
    if (hit->object) actor->blocked = 1;
    SetMotionVector(&normal, hit->plane->normalX, hit->plane->normalY, hit->plane->normalZ);
    VEC_Subtract(position, &actor->position, &delta);
    delta.y = 0;
    opposite.x = -normal.x;
    opposite.y = -normal.y;
    opposite.z = -normal.z;
    scale = VEC_DotProduct(&delta, &opposite);
    scale = FX_Div(scale, VEC_DotProduct(&opposite, &opposite));
    VEC_MultAdd(scale, &opposite, &gZeroVecFx32, &projection);
    VEC_Subtract(&delta, &projection, &deflection);
    if (!actor->wallMotion) {
        fx32 cosine;
        opposite.x = -normal.x;
        opposite.y = -normal.y;
        opposite.z = -normal.z;
        VEC_NormalizeLength(&delta, &normalized);
        cosine = VEC_DotProduct(&opposite, &normalized);
        if (cosine < 0) cosine = -cosine;
        scale = FX_Mul(0xcd, 0x1000 - cosine);
        if (scale <= 0) scale = 0x29;
        VEC_MultAdd(scale, &normal, motion, motion);
    } else {
        SetMotionVector(&normal, hit->plane->normalX, 0, hit->plane->normalZ);
        scale = 0xcd;
        VEC_MultAdd(scale, &normal, motion, motion);
    }
    scale = VEC_NormalizeLength(&deflection, &deflection);
    if (actor->wallMotion) {
        CollisionHit *farHit;
        if (scale < 4) {
            deflection.x = normal.z;
            deflection.y = normal.y;
            deflection.z = normal.x;
        }
        VEC_MultAdd(0x2000, &deflection, &gZeroVecFx32, &step);
        nearHit = SweepActorStep(actor, motion, &step, &nearEnd);
        if (!nearHit) {
            deflection = step;
        } else {
            VEC_MultAdd(-0x2000, &deflection, &gZeroVecFx32, &step);
            farHit = SweepActorStep(actor, motion, &step, &farEnd);
            if (!farHit) {
                deflection = step;
            } else if (nearHit && farHit) {
                if (nearHit->sortKey > farHit->sortKey)
                    VEC_Subtract(&nearEnd, motion, &deflection);
                else
                    VEC_Subtract(&farEnd, motion, &deflection);
            }
        }
    }
    if (actor->maxCorrection) {
        fx32 limit;
        actor->correction = deflection;
        limit = actor->maxCorrection;
        fx32 magnitude = VEC_Mag(&actor->correction);
        if (magnitude > ((int)limit >> 1)) {
            VEC_NormalizeLength(&actor->correction, &actor->correction);
            ScaleVecFx32InPlace(&actor->correction, limit >> 1);
        }
    }
    position->x = motion->x;
    position->z = motion->z;
}
