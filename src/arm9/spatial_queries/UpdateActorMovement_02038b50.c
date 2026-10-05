#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorBody {
    u8 pad_000[0xa8];
    VecFx32 position;
    u8 pad_0b4[0x14c - 0xb4];
    s32 groundState;
} ActorBody;

typedef struct MoveActor {
    ActorBody *body;
    u32 flags;
    VecFx32 velocity;
    VecFx32 impulse;
    VecFx32 drift;
    fx32 fallSpeed;
    fx32 fallAccel;
    fx32 maxFallSpeed;
    u8 pad_38[2];
    s16 state;
    u8 pad_3c[4];
    fx32 planeHeight;
    u8 pad_44[0x108 - 0x44];
    s32 unk_108;
    u8 pad_10c[4];
    fx32 speedScale;
    u8 pad_114[0x1d4 - 0x114];
    VecFx32 guideAxes[16];
    u8 guideAxisCount;
} MoveActor;

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_Normalize_01ff9f88(const VecFx32 *source, VecFx32 *dest);
extern void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern VecFx32 *GetModeContext_02036cd8(void);
extern void MoveActorAndSnapToGround_02037870(VecFx32 *pos, VecFx32 *vel, MoveActor *actor, u32 flags);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern VecFx32 GetUnitRejectionFromAxis_0204aea8(const VecFx32 *vec, const VecFx32 *axis);
extern void RotateVecTowardVec_0204b0ac(VecFx32 *vec, const VecFx32 *target, fx32 angle);
extern s32 func_ov001_02063a38(void);
extern s32 func_ov001_02063a4c(void);
extern const VecFx32 data_02053438;

static inline BOOL IsMode4(void)
{
    return func_ov001_02063a38() == 4;
}

static inline BOOL IsMode7(void)
{
    return func_ov001_02063a38() == 7;
}

static inline BOOL IsGravityWorld(void)
{
    BOOL inMode;
    BOOL result = FALSE;
    if (func_ov001_02063a4c() >= 4 && func_ov001_02063a4c() <= 9) {
        inMode = TRUE;
        if (!IsMode4() && !IsMode7()) {
            inMode = FALSE;
        }
        if (inMode) {
            result = TRUE;
        }
    }
    return result;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}


static inline VecFx32 UnitCross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 side;
    VecFx32 cross;
    VecFx32 result;
    VEC_CrossProduct_01ff9ea8(a, b, &cross);
    side = cross;
    VEC_Normalize_01ff9f88(&side, &result);
    return result;
}


static inline VecFx32 VecRotatedToward(const VecFx32 *v, const VecFx32 *target, fx32 angle)
{
    VecFx32 result = *v;
    RotateVecTowardVec_0204b0ac(&result, target, angle);
    return result;
}

static inline VecFx32 VecMultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 result;
    VEC_MultAdd_01ffa09c(scale, v, add, &result);
    return result;
}

static inline VecFx32 VecRejectAxis(const VecFx32 *v, const VecFx32 *axis, fx32 dot)
{
    VecFx32 projection;
    VecFx32 scaled;
    VecFx32 result;
    scaled = *axis;
    ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
    projection = scaled;
    VEC_Subtract_01ff9e3c(v, &projection, &result);
    return result;
}

BOOL UpdateActorMovement_02038b50(MoveActor *actor, VecFx32 *pos)
{
    VecFx32 move;
    VecFx32 *bodyPos;
    u32 flags;

    if (actor->state < 0) {
        return FALSE;
    }
    bodyPos = &actor->body->position;
    flags = actor->flags;
    if ((flags & 0x400) && (actor->velocity.x != 0 || actor->velocity.y != 0 || actor->velocity.z != 0)) {
        VecFx32 sideUnit;
        VecFx32 guided;
        VecFx32 up;
        up = MakeVec(0, 0x1000, 0);
        sideUnit = UnitCross(&up, &actor->velocity);
        *(VecFx32 *)&guided = GetUnitRejectionFromAxis_0204aea8(&actor->guideAxes[actor->guideAxisCount - 1], &sideUnit);
        move = VecRotatedToward(&guided, &actor->velocity, 0x1922);
        ScaleVecFx32InPlace_0204a5e4(&move, VEC_Mag_01ff9f28(&actor->velocity));
    } else if (!(flags & 4) && (actor->drift.x != 0 || actor->drift.y != 0 || actor->drift.z != 0)) {
        fx32 mag;
        move = actor->drift;
        mag = VEC_Mag_01ff9f28(&actor->drift);
        if (mag <= 0x7b) {
            actor->drift = data_02053438;
        } else {
            func_01ffaff4(&actor->drift, &actor->drift);
            ScaleVecFx32InPlace_0204a5e4(&actor->drift, mag - 0x7b);
        }
    } else if (flags & 0x80) {
        VEC_Add_01ff9e0c(&actor->velocity, &actor->impulse, &move);
        actor->impulse = data_02053438;
    } else {
        move = actor->velocity;
    }

    actor->flags &= ~0x3c8e;
    actor->unk_108 = 0;
    if (actor->speedScale != 0x1000) {
        ScaleVecFx32_01ffafb4(actor->speedScale, &move, &move);
    }
    *pos = *bodyPos;
    if ((actor->flags & 0x10) && actor->fallSpeed != (fx32)0x80000000) {
        fx32 accel = FixedPointMultiply12(actor->fallAccel, 0x1000);
        fx32 fall = FixedPointMultiply12(actor->fallSpeed, 0x1000);
        actor->fallSpeed -= accel;
        if (actor->fallSpeed < -actor->maxFallSpeed) {
            actor->fallSpeed = -actor->maxFallSpeed;
        }
        move.y += fall;
    }
    if (IsGravityWorld()) {
        VecFx32 *gravity = GetModeContext_02036cd8();
        fx32 dot = VEC_DotProduct_01ff9e6c(&move, gravity);
        move = VecRejectAxis(&move, gravity, dot);
    }
    if (actor->body->groundState != -1) {
        MoveActorAndSnapToGround_02037870(pos, &move, actor, flags);
    } else {
        VEC_Add_01ff9e0c(pos, &move, pos);
    }
    if (IsGravityWorld()) {
        VecFx32 *gravity = GetModeContext_02036cd8();
        fx32 height = VEC_DotProduct_01ff9e6c(pos, gravity);
        fx32 diff = actor->planeHeight - height;
        if ((diff < 0 ? -diff : diff) < 0x10) {
            *pos = VecMultAdd(diff, gravity, pos);
        } else {
            actor->planeHeight = height;
        }
    }
    actor->flags &= ~0x40;
    actor->flags &= ~0x1000;
    return TRUE;
}















