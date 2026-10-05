#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 data[0x40];
} BoxStorage;

typedef struct {
    u8 data[0x28];
} SegmentStorage;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x14];
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef union {
    u32 raw;
    struct {
        u32 bit0 : 1;
        u32 bit1 : 1;
        u32 solid : 1;
    } bits;
} SweepFilterArg;

typedef struct {
    u32 words[0x2e];
} CollisionHit;

typedef struct {
    VecFx32 position;
    CollisionHit hit;
    int timer;
    u16 angle;
} DashState;

typedef struct Actor Actor;
typedef void (*ModeFunc)(Actor *actor, int mode, int arg);
typedef void (*NotifyFunc)(Actor *actor, int arg);
typedef int (*StateGetter)(Actor *actor);
typedef void (*EventFunc)(Actor *actor, int event);

struct Actor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x1f8 - 0x1e0];
    ModeFunc onMode;
    NotifyFunc onNotify;
    u8 pad_0200[0x22c - 0x200];
    StateGetter getState;
    void *object;
    u8 pad_0234[0x75c - 0x234];
    int mode;
    u8 pad_0760[0x768 - 0x760];
    BOOL modeChangePending;
    u8 pad_076c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 player;
    u8 pad_09b5[0x9c8 - 0x9b5];
    VecFx32 velocity;
    u8 pad_09d4[0xa54 - 0x9d4];
    DashState dash;
    u8 pad_0b20[0x10ec - 0xb20];
    EventFunc onEvent;
};

extern s16 data_0205356c[];
extern void *func_ov001_0206db78(int player);
extern BOOL HasFlagsAt0xe_020a752c(void *unit, u16 mask);
extern BOOL HasFlagsAt0xc_020a751c(void *unit, u16 mask);
extern BOOL func_ov052_020c847c(Actor *actor, int forward);
extern void ComputeRootMotionDelta_020ce9d4(Actor *actor, VecFx32 *out);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov052_020ceb60(Actor *actor, VecFx32 *position);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void RotateOffsetAroundY_020a9160(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void InitBoxShape_0203ad54(CollisionShape *shape, BoxStorage *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void func_ov021_020a9268(void);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape func_0203adcc(SegmentStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void EnterRecoilState_020c957c(Actor *actor);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern BOOL func_ov001_0206e2b0(void);
extern void AddSessionCounter_02063a80(int index, int amount);

static inline int GetActorState(Actor *actor)
{
    if (actor->getState != NULL) {
        return actor->getState(actor);
    }
    return actor->state;
}

static inline void VecSet(VecFx32 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void UpdateWallSlide_020cba24(Actor *actor)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery boxQuery;
    CollisionQuery segQuery;
    SegmentStorage segStorage;
    CollisionShape shapeCopy;
    VecFx32 top;
    VecFx32 bottom;
    VecFx32 dir;
    VecFx32 delta;
    BoxStorage boxStorage;
    VecFx32 center;
    VecFx32 halfExtents;
    MtxFx33 rotation;
    VecFx32 velocity;
    CollisionShape boxShape;
    CollisionShape segShape;
    VecFx32 diff;
    VecFx32 axis;
    SweepFilterArg filterArg;
    QueryCallback callback;
    void *unit = func_ov001_0206db78(actor->player);
    BOOL recoil;
    BOOL blocked;
    BOOL jump;
    int angle;
    int phase;
    DashState *dash = &actor->dash;

    phase = 0;
    recoil = FALSE;
    blocked = FALSE;
    jump = FALSE;
    if (actor->mode != 0x17) {
        phase = 1;
    }
    switch (phase) {
    case 0:
        if (dash->timer > 0) {
            break;
        }
        if (HasFlagsAt0xe_020a752c(unit, 0x40)) {
            if (func_ov052_020c847c(actor, 1) && actor->onMode != NULL) {
                actor->onMode(actor, 0x18, -1);
            }
        } else if (HasFlagsAt0xe_020a752c(unit, 0x80)) {
            if (func_ov052_020c847c(actor, 0)) {
                if (actor->onMode != NULL) {
                    actor->onMode(actor, 0x19, -1);
                }
            } else {
                recoil = TRUE;
            }
        }
        break;
    case 1:
        ComputeRootMotionDelta_020ce9d4(actor, &delta);
        VEC_Add_01ff9e0c(func_ov052_020ceb54(actor), &delta, &dash->position);
        if (actor->modeChangePending) {
            BOOL handled = FALSE;
            if (HasFlagsAt0xe_020a752c(unit, 0x40) && actor->mode == 0x18) {
                if (func_ov052_020c847c(actor, 1)) {
                    if (actor->onNotify != NULL) {
                        actor->onNotify(actor, 0);
                    }
                    handled = TRUE;
                }
            } else if (HasFlagsAt0xe_020a752c(unit, 0x80) && actor->mode == 0x19) {
                if (func_ov052_020c847c(actor, 0)) {
                    if (actor->onNotify != NULL) {
                        actor->onNotify(actor, 0);
                    }
                    handled = TRUE;
                } else {
                    recoil = TRUE;
                }
            }
            if (!handled && actor->onMode != NULL) {
                actor->onMode(actor, 0x17, -1);
            }
        }
        break;
    }
    func_ov052_020ceb60(actor, &dash->position);
    actor->stateFlags |= 1;
    if (!(actor->stateFlags & 0x80000000) && (actor->stateFlags & 0x20)) {
        recoil = TRUE;
    }
    if (GetActorState(actor) != 6 && HasFlagsAt0xc_020a751c(unit, 2)) {
        jump = TRUE;
    }
    filterArg.raw = 0;
    filterArg.bits.solid = 1;
    angle = (u16)(GetLinkedAngleOffset_020ceb7c(actor) - 0x8000);
    MTX_RotY33_01ff923c(&rotation, -data_0205356c[angle >> 4], -data_0205356c[(0x400 - (angle >> 4)) & 0xfff]);
    center.y = 0xa66;
    center.x = 0;
    center.z = 0;
    RotateOffsetAroundY_020a9160(&center, &dash->position, angle, &center);
    halfExtents.x = 0x5cd;
    halfExtents.y = 0xfbd;
    halfExtents.z = 0x333;
    InitBoxShape_0203ad54(&boxShape, &boxStorage, &center, &halfExtents, &rotation);
    shapeCopy = boxShape;
    CollisionQuery_Init_02034c74(&boxQuery, 0, actor->object, 9, 2, 0, &shapeCopy, &workspace, NULL);
    sweep = boxQuery;
    callback.func = func_ov021_020a9268;
    callback.arg = &filterArg;
    sweep.callback = callback;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        recoil = TRUE;
    }
    dir.z = 0;
    dir.y = 0;
    dir.x = 0;
    angle = GetLinkedAngleOffset_020ceb7c(actor);
    dir.x = -data_0205356c[angle >> 4];
    dir.z = -data_0205356c[(0x400 - (angle >> 4)) & 0xfff];
    VEC_MultAdd_01ffa09c(0x800, &dir, &dash->position, &top);
    bottom = top;
    top.y += 0x15d7;
    VEC_Subtract_01ff9e3c(&bottom, &top, &diff);
    axis = diff;
    segShape = func_0203adcc(&segStorage, &top, &bottom, &axis, func_01ffaff4(&axis, &axis));
    shapeCopy = segShape;
    CollisionQuery_Init_02034c74(&segQuery, 0, actor->object, 1, 1, 0, &shapeCopy, &workspace, NULL);
    sweep = segQuery;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        blocked = TRUE;
    }
    if (recoil) {
        EnterRecoilState_020c957c(actor);
        return;
    }
    if (blocked) {
        actor->onEvent(actor, 7);
        return;
    }
    if (jump) {
        angle = (u16)(GetLinkedAngleOffset_020ceb7c(actor) + 0x8000);
        velocity.z = 0;
        velocity.y = 0;
        velocity.x = 0;
        velocity.x = -data_0205356c[angle >> 4];
        velocity.z = -data_0205356c[(0x400 - (angle >> 4)) & 0xfff];
        ScaleVecFx32_01ffafb4(0x100, &velocity, &velocity);
        velocity.y = 0x580;
        if (IsPlayerEntryFlagSet_02050014(0, 0xc) && !func_ov001_0206e2b0()) {
            velocity.y = 0x740;
        }
        VecSet(&actor->velocity, velocity.x, velocity.y, velocity.z);
        actor->onEvent(actor, 3);
        AddSessionCounter_02063a80(9, 1);
    }
}
