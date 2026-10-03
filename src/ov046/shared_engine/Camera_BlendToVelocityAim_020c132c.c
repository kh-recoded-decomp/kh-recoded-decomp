#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 velocity;
    u8 pad_18[0x10];
} CameraView;

typedef void (*CameraViewBuilder)(CameraView *view);

extern void Camera_AimAlongVelocity_020c199c(CameraView *view);
extern void func_ov046_020c10d4(s32 returnMode, CameraView *view, s32 curveType, fx32 duration,
                                CameraViewBuilder builder);

void Camera_BlendToVelocityAim_020c132c(const VecFx32 *velocity, s32 curveType, fx32 duration)
{
    CameraView view;

    view.velocity = *velocity;
    Camera_AimAlongVelocity_020c199c(&view);
    func_ov046_020c10d4(0, &view, curveType, duration, Camera_AimAlongVelocity_020c199c);
}
