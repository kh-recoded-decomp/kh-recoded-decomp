#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraManager {
    u8 pad_00[0x88];
    u8 motion[0x48];
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern MtxFx43 data_0205a970;
extern void MTX_Copy43To33_01ff913c(const MtxFx43 *src, MtxFx33 *dst);
extern void func_ov021_020afa70(void *motion, const VecFx32 *forward, const VecFx32 *offset, s32 duration, s32 arg4, s32 arg5);

static inline MtxFx33 GetViewRotation(void)
{
    MtxFx33 rotation;
    MTX_Copy43To33_01ff913c(&data_0205a970, &rotation);
    return rotation;
}

void Camera_StartViewMotion_020c0f8c(const VecFx32 *offset, s32 duration, s32 arg4, s32 arg5)
{
    MtxFx33 rotation = GetViewRotation();
    func_ov021_020afa70(g_cameraManager_020c34e0->motion, (const VecFx32 *)rotation.m[2], offset, duration, arg4, arg5);
}
