#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x24];
    s32 arrived;
} CameraTrackState;

extern const VecFx32 data_ov058_020d899c;
extern CameraTrackState data_ov058_020d8a24;
extern VecFx32 data_ov058_020d8a2c;

extern int func_ov058_020d88e4(int mode);
extern void RotateOffsetAroundY_020a9160(VecFx32 *out, const VecFx32 *origin, int angle, const VecFx32 *offset);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);

void ComputeApproachTarget_020d8814(VecFx32 *out, int mode)
{
    CameraTrackState *state = &data_ov058_020d8a24;
    VecFx32 target;
    VecFx32 diff;
    VecFx32 offset = data_ov058_020d899c;

    RotateOffsetAroundY_020a9160(&target, &data_ov058_020d8a2c, func_ov058_020d88e4(mode), &offset);
    if (mode == 0 && state->arrived == 0) {
        VEC_Subtract_01ff9e3c(&target, func_ov001_0206dc4c(mode), &diff);
        if (VEC_Mag_01ff9f28(&diff) <= 0x19a) {
            state->arrived = 1;
        } else {
            func_01ffaff4(&diff, &diff);
            VEC_MultAdd_01ffa09c(0x19a, &diff, &target, &target);
        }
    }
    *out = target;
}
