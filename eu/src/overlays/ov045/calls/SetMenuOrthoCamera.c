#include "src/graphics/CameraMaterialState.h"

void SetMenuOrthoCamera(fx32 left, fx32 right, fx32 top, fx32 bottom)
{
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;

    MTX_OrthoW(top, bottom, left, right,
               0, 3 * FX32_ONE, 1024 * FX32_ONE, &NNS_G3dGlb_projMtx);
    NNS_G3dGlb_prmMatColor0.dirtyFlags &= ~0x50;
    up.y = FX32_ONE;
    position.y = 0;
    position.x = 0;
    up.z = 0;
    up.x = 0;
    target.z = 0;
    target.y = 0;
    target.x = 0;
    position.z = 1024 * FX32_ONE;
    NNS_G3dGlb_prmMatColor0.position = position;
    NNS_G3dGlb_prmMatColor0.up = up;
    NNS_G3dGlb_prmMatColor0.target = target;
    func_01ff9b70(&position, &up, &target, &NNS_G3dGlb_cameraMtx);
    NNS_G3dGlb_prmMatColor0.dirtyFlags &= ~0xe8;
}
