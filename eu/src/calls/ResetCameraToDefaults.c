#include "src/graphics/CameraState.h"

extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

int ResetCameraToDefaults(void)
{
    MIi_CpuCopyFast(&gSavedCameraState.projection, &NNS_G3dGlb.projection, sizeof(MtxFx44));
    NNS_G3dGlb.flags &= ~0x50;
    NNS_G3dGlb.position = gSavedCameraState.position;
    NNS_G3dGlb.up = gSavedCameraState.up;
    NNS_G3dGlb.target = gSavedCameraState.target;
    func_01ff9b70(&gSavedCameraState.position, &gSavedCameraState.up,
                 &gSavedCameraState.target, &NNS_G3dGlb.camera);
    NNS_G3dGlb.flags &= ~0xe8;
    return 0;
}
