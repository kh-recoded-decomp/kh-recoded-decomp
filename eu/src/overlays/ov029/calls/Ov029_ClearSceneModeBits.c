#include "src/overlays/ov029/Ov029SceneState.h"

s32 Ov029_ClearSceneModeBits(void)
{
    Ov029SceneState *state = gOv029SceneWorkStorage;

    state->flags &= 0xfff3;
    return -1;
}
