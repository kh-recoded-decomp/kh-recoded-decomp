#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTracking {
    u8 pad_00[0xc];
    fx32 distance;
    u32 angle;
    fx32 height;
    fx32 lift;
    fx32 eyeDistance;
    u8 pad_20[0x30 - 0x20];
    VecFx32 target;
    u8 pad_3c[0x54 - 0x3c];
    VecFx32 direction;
} CameraTracking;

typedef struct CameraManager {
    u8 pad_00[0xf0];
    u32 stateFlags;
    u8 pad_f4[0x13c - 0xf4];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void Camera_ResolveCollision_020c1e54(VecFx32 *position);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov046_020c1fa0(VecFx32 *target, VecFx32 *eye);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline VecFx32 ScaledVec(const VecFx32 *vec, fx32 scale)
{
    VecFx32 result = *vec;
    ScaleVecFx32InPlace_0204a5e4(&result, scale);
    return result;
}

void Camera_PlaceTrackingEye_020c4880(VecFx32 *target, VecFx32 *eye, void *unused, const VecFx32 *focus)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    CameraTracking *tracking = (CameraTracking *)camera->controllerData;
    VecFx32 eyePos;

    SetVec(target, focus->x, focus->y + tracking->lift, focus->z);
    Camera_ResolveCollision_020c1e54(target);
    eyePos = ScaledVec(&tracking->direction, -tracking->distance);
    VEC_Add_01ff9e0c(&eyePos, &tracking->target, &eyePos);
    *eye = eyePos;
    if (!(camera->stateFlags & 0x10000)) {
        func_ov046_020c1fa0(&tracking->target, &eyePos);
    }
    *eye = eyePos;
    tracking->eyeDistance = func_01ffa0f4(&tracking->target, eye);
}

