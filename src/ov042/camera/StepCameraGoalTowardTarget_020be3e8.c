#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 _0[0x70];
    VecFx32 goalEye;
    u8 _7c[0xc];
    VecFx32 goalTarget;
    VecFx32 desiredEye;
    u8 _a0[0xa4];
    int locked;
} CameraState;

extern CameraState *data_ov042_020be5c0;
extern int func_ov001_02063a4c(void);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *source, VecFx32 *destination);
extern int FixedPointMultiply12(int left, int right);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void TranslateCameraGoal_020bd1ec(const VecFx32 *offset);
extern void SetCameraGoalTarget_020bd234(const VecFx32 *pos);

BOOL StepCameraGoalTowardTarget_020be3e8(void) {
    CameraState *camera = data_ov042_020be5c0;
    VecFx32 dir;
    VecFx32 offset;
    VecFx32 scaled;
    fx32 dist;
    fx32 step;
    BOOL arrived;

    if (func_ov001_02063a4c() != 7 && func_ov001_02063a4c() != 8) {
        camera->locked = 0;
    }
    if (camera->locked != 0) {
        SetCameraGoalTarget_020bd234(&camera->goalTarget);
    } else {
        VEC_Subtract_01ff9e3c(&camera->desiredEye, &camera->goalEye, &dir);
        dist = VEC_Normalize_01ffaff4(&dir, &dir);
        if (dist != 0) {
            arrived = TRUE;
            if (dist > 0x10) {
                arrived = FALSE;
            }
            if (!arrived) {
                step = FixedPointMultiply12(dist, 0x300);
                if (step > dist) {
                    step = dist;
                } else if (step < 0) {
                    step = 0;
                }
                if (step >= dist) {
                    arrived = TRUE;
                } else {
                    scaled = dir;
                    ScaleVecFx32InPlace_0204a5e4(&scaled, step);
                    offset = scaled;
                    TranslateCameraGoal_020bd1ec(&offset);
                }
            }
            if (arrived) {
                SetCameraGoalTarget_020bd234(&camera->goalTarget);
            }
        }
    }
    return TRUE;
}