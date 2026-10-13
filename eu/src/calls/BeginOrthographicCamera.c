#include "src/graphics/CameraState.h"

extern void MTX_OrthoW(fx32 top, fx32 bottom, fx32 left, fx32 right,
                      fx32 nearPlane, fx32 farPlane, fx32 scaleW, MtxFx44 *matrix);

int BeginOrthographicCamera(void)
{
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;

    gSavedCameraState.position = NNS_G3dGlb.position;
    gSavedCameraState.up = NNS_G3dGlb.up;
    gSavedCameraState.target = NNS_G3dGlb.target;
    gSavedCameraState.projection = NNS_G3dGlb.projection;
    gSavedCameraState.camera = NNS_G3dGlb.camera;

    MTX_OrthoW(192 * FX32_ONE, 0, 0, 256 * FX32_ONE,
               0, 3 * FX32_ONE, 1024 * FX32_ONE, &NNS_G3dGlb.projection);
    position.y = 0;
    position.x = 0;
    position.z = 1024 * FX32_ONE;
    up.z = 0;
    up.y = FX32_ONE;
    up.x = 0;
    target.z = 0;
    target.y = 0;
    target.x = 0;

    NNS_G3dGlb.flags &= ~0x50;
    NNS_G3dGlb.position = position;
    NNS_G3dGlb.up = up;
    NNS_G3dGlb.target = target;
    func_01ff9b70(&position, &up, &target, &NNS_G3dGlb.camera);
    NNS_G3dGlb.flags &= ~0xe8;
    return 0;
}
