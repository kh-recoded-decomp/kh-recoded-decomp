#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x14];
    VecFx32 target;
    VecFx32 position;
    u8 pad_2C[0xc];
    VecFx32 basePosition;
    VecFx32 baseTarget;
    u8 pad_50[0x48];
    VecFx32 offset;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_ov001_02067ed4(void);
extern s32 func_ov001_0206805c(int index);

void Camera_ApplyOffsetClampHeight_020c0a24(void)
{
    VEC_Add_01ff9e0c(&g_cameraManager_020c34e0->basePosition, &g_cameraManager_020c34e0->offset, &g_cameraManager_020c34e0->position);
    VEC_Add_01ff9e0c(&g_cameraManager_020c34e0->baseTarget, &g_cameraManager_020c34e0->offset, &g_cameraManager_020c34e0->target);
    if (func_ov001_02067ed4() != -1) {
        s32 limit = func_ov001_0206805c(func_ov001_02067ed4());
        g_cameraManager_020c34e0->position.y = (g_cameraManager_020c34e0->position.y <= limit) ? g_cameraManager_020c34e0->position.y : limit;
    }
}
