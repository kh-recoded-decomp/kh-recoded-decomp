#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraMotion {
    VecFx32 position;
    VecFx32 velocity;
} CameraMotion;

extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void func_ov046_020c179c(CameraMotion *motion, u16 heading);

void Camera_AimAlongVelocity_020c199c(CameraMotion *motion)
{
    func_ov046_020c179c(motion, FixedPointAtan2_020062bc(motion->velocity.z, motion->velocity.x));
}
