#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
} CameraView;

typedef struct CameraManager {
    u8 pad_00[0x134];
    fx32 viewDistance;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void Camera_GetRaisedPlayerPosition_020c14a8(VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline void NormalizeVec(VecFx32 vec, VecFx32 *out)
{
    func_01ff9f88(&vec, out);
}

void Camera_AimViewAtPlayer_020c32f0(CameraView *view)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    VecFx32 focus;
    VecFx32 direction;
    VecFx32 delta;

    Camera_GetRaisedPlayerPosition_020c14a8(&focus);
    VEC_Subtract_01ff9e3c(&focus, &view->position, &delta);
    NormalizeVec(delta, &direction);
    view->direction = direction;
    view->up = MakeVec(0, 0x1000, 0);
    VEC_MultAdd_01ffa09c(-camera->viewDistance, &view->direction, &focus, &view->position);
}
