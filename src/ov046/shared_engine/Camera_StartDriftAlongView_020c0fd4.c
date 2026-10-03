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
extern void InitDriftParticle_020afb34(void *particle, const VecFx32 *position, int param30, int param2c);

static inline MtxFx33 GetViewRotation(void)
{
    MtxFx33 rotation;
    MTX_Copy43To33_01ff913c(&data_0205a970, &rotation);
    return rotation;
}

void Camera_StartDriftAlongView_020c0fd4(int param30, int param2c)
{
    MtxFx33 rotation = GetViewRotation();
    InitDriftParticle_020afb34(g_cameraManager_020c34e0->motion, (const VecFx32 *)rotation.m[2], param30, param2c);
}
