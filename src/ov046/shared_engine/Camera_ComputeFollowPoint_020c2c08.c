#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x12c];
    fx32 followDistance;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov046_020c2c4c(void *offsetSource, s32 unused, VecFx32 *out);

void Camera_ComputeFollowPoint_020c2c08(void *offsetSource, s32 unused, const VecFx32 *direction,
                                        VecFx32 *out)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    VecFx32 offset;

    VEC_MultAdd_01ffa09c(camera->followDistance, direction, func_ov001_0206dc4c(0), out);
    func_ov046_020c2c4c(offsetSource, unused, &offset);
    VEC_Add_01ff9e0c(out, &offset, out);
}
