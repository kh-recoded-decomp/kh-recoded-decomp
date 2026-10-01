#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 Camera_GetViewDirectionAtAngle_020af8d4(s32 angle);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void Camera_StartViewMotion_020c0f8c(const VecFx32 *offset, s32 duration, s32 arg4, s32 arg5);

static inline VecFx32 Scaled(VecFx32 vec, fx32 scale)
{
    func_0204a5e4(&vec, scale);
    return vec;
}

void Camera_StartViewMotionAtAngle_020c0f44(s32 angle, fx32 distance, s32 duration, s32 arg4, s32 arg5)
{
    VecFx32 offset = Scaled(Camera_GetViewDirectionAtAngle_020af8d4(angle), distance);
    Camera_StartViewMotion_020c0f8c(&offset, duration, arg4, arg5);
}
