#include "src/overlays/ov029/Ov029SceneState.h"

s32 Ov029_ClearSceneModeBits(void)
{
    Ov029SceneState *state = data_ov029_020babc0;

    state->flags &= 0xfff3;
    return -1;
}
