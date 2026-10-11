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

extern CameraFrame *data_ov042_020be5e0;
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *result);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *result);
extern void SetSoundListenerFrame(const VecFx32 *position, const VecFx32 *direction, const VecFx32 *up);
extern void CommitCameraProjection(CameraFrame *camera, fx32 top, fx32 bottom, fx32 left, fx32 right);

static inline void ApplyCameraShake(void)
{
    CameraFrame *camera = data_ov042_020be5e0;
    VecFx32 targetSum;
    VecFx32 eyeSum;

    VEC_Add(&camera->baseTarget, &camera->shake, &targetSum);
    camera->target = targetSum;
    VEC_Add(&data_ov042_020be5e0->baseEye, &data_ov042_020be5e0->shake, &eyeSum);
    camera->eye = eyeSum;
}

void CommitCameraFrame(BOOL updateSoundListener)
{
    CameraFrame *camera = data_ov042_020be5e0;

    if (!(camera->flags & 4)) {
        ApplyCameraShake();
        if (updateSoundListener) {
            VecFx32 direction;
            VEC_Subtract(&camera->eye, &camera->target, &direction);
            SetSoundListenerFrame(&camera->target, &direction, &camera->up);
        }
        CommitCameraProjection(camera, camera->top, camera->bottom, camera->left, camera->right);
    }
}
