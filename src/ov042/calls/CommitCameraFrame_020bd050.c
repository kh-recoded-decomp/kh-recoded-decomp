#include "nitro/fx_types.h"

typedef struct CameraFrame {
    u8 reserved00[0x14];
    VecFx32 eye;
    VecFx32 target;
    VecFx32 up;
    u32 flags;
    u8 reserved3c[0x18];
    fx32 left;
    fx32 right;
    fx32 top;
    fx32 bottom;
    VecFx32 baseTarget;
    VecFx32 baseEye;
    VecFx32 shake;
} CameraFrame;

extern CameraFrame *data_ov042_020be5c0;
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *result);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *result);
extern void SetSoundListenerFrame_0204dc94(const VecFx32 *position, const VecFx32 *direction, const VecFx32 *up);
extern void CommitCameraProjection_020bd020(CameraFrame *camera, fx32 top, fx32 bottom, fx32 left, fx32 right);

static inline void ApplyCameraShake(void)
{
    CameraFrame *camera = data_ov042_020be5c0;
    VecFx32 targetSum;
    VecFx32 eyeSum;

    VEC_Add_01ff9e0c(&camera->baseTarget, &camera->shake, &targetSum);
    camera->target = targetSum;
    VEC_Add_01ff9e0c(&data_ov042_020be5c0->baseEye, &data_ov042_020be5c0->shake, &eyeSum);
    camera->eye = eyeSum;
}

void CommitCameraFrame_020bd050(BOOL updateSoundListener)
{
    CameraFrame *camera = data_ov042_020be5c0;

    if (!(camera->flags & 4)) {
        ApplyCameraShake();
        if (updateSoundListener) {
            VecFx32 direction;
            VEC_Subtract_01ff9e3c(&camera->eye, &camera->target, &direction);
            SetSoundListenerFrame_0204dc94(&camera->target, &direction, &camera->up);
        }
        CommitCameraProjection_020bd020(camera, camera->top, camera->bottom, camera->left, camera->right);
    }
}
