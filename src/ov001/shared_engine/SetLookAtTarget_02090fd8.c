#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LookAtState {
    u8 pad_000[0x2c0];
    VecFx32 eye;
    u8 pad_2cc[0xc];
    VecFx32 target;
    u8 pad_2e4[2];
    u16 currentYaw;
    u16 yaw;
    u16 currentPitch;
    u16 pitch;
} LookAtState;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);

static inline u16 ComputeYaw(const VecFx32 *to, const VecFx32 *from)
{
    VecFx32 dir;

    VEC_Subtract_01ff9e3c(to, from, &dir);
    if (func_01ffaff4(&dir, &dir) != 0) {
        return FixedPointAtan2_020062bc(dir.x, dir.z);
    }
    return 0;
}

static inline fx32 ComputePitch(const VecFx32 *to, const VecFx32 *from)
{
    VecFx32 dir;
    VecFx32 flat;
    fx32 angle;

    VEC_Subtract_01ff9e3c(to, from, &dir);
    if (func_01ffaff4(&dir, &dir) == 0) {
        return 0;
    }
    flat = dir;
    flat.y = 0;
    angle = 0x4000000 - (VEC_DotProduct_01ff9e6c(&flat, &dir) << 14);
    if (dir.y > 0) {
        angle *= -1;
        angle += 0xffff000;
    }
    return angle >> 12;
}

void SetLookAtTarget_02090fd8(LookAtState *state, const VecFx32 *target, BOOL keepCurrent)
{
    if (target == NULL) {
        return;
    }
    state->target = *target;
    state->yaw = ComputeYaw(target, &state->eye);
    state->pitch = ComputePitch(target, &state->eye);
    if (!keepCurrent) {
        state->currentYaw = state->yaw;
        state->currentPitch = state->pitch;
    }
}
