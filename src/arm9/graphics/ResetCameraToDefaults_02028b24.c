#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct G3dGlobalState {
    u32 unk_00;
    u32 unk_04;
    MtxFx44 projectionMtx;
    u32 unk_48;
    MtxFx43 cameraMtx;
    u8 pad_7C[0x58];
    u32 flags;
} G3dGlobalState;

typedef struct CameraVectors {
    VecFx32 position;
    VecFx32 up;
    VecFx32 target;
} CameraVectors;

typedef struct CameraDefaults {
    VecFx32 target;
    VecFx32 position;
    VecFx32 up;
    MtxFx44 projectionMtx;
} CameraDefaults;

extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, MtxFx43 *mtx);

extern G3dGlobalState g_g3dGlobal_0205a924;
extern CameraDefaults g_cameraDefaults_0205fe28;
extern CameraVectors g_camera_0205ab3c;

int ResetCameraToDefaults_02028b24(void)
{
    MIi_CpuCopyFast_01ff878c(&g_cameraDefaults_0205fe28.projectionMtx, &g_g3dGlobal_0205a924.projectionMtx, sizeof(MtxFx44));
    g_g3dGlobal_0205a924.flags &= ~0x50;
    g_camera_0205ab3c.position = g_cameraDefaults_0205fe28.position;
    g_camera_0205ab3c.up = g_cameraDefaults_0205fe28.up;
    g_camera_0205ab3c.target = g_cameraDefaults_0205fe28.target;
    func_01ff9b70(&g_cameraDefaults_0205fe28.position, &g_cameraDefaults_0205fe28.up, &g_cameraDefaults_0205fe28.target, &g_g3dGlobal_0205a924.cameraMtx);
    g_g3dGlobal_0205a924.flags &= ~0xe8;
    return 0;
}
