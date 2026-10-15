#include "src/graphics/CameraMaterialState.h"

void SetScreenOrthoCamera(void)
{
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;

    MTX_OrthoW(192 * FX32_ONE, 0, 0, 256 * FX32_ONE,
               0, 3 * FX32_ONE, 1024 * FX32_ONE, &NNS_G3dGlb_projMtx);
    position.y = 0;
    position.x = 0;
    position.z = 1024 * FX32_ONE;
    NNS_G3dGlb_prmMatColor0.dirtyFlags &= ~0x50;
    up.y = FX32_ONE;
    up.z = 0;
    up.x = 0;
    target.z = 0;
    target.y = 0;
    target.x = 0;
    NNS_G3dGlb_prmMatColor0.position = position;
    NNS_G3dGlb_prmMatColor0.up = up;
    NNS_G3dGlb_prmMatColor0.target = target;
    func_01ff9b70(&position, &up, &target, &NNS_G3dGlb_cameraMtx);
    NNS_G3dGlb_prmMatColor0.dirtyFlags &= ~0xe8;
}
