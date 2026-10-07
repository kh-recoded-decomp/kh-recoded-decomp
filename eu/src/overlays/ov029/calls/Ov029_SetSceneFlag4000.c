#include "src/overlays/ov029/Ov029SceneState.h"

s32 Ov029_SetSceneFlag4000(void)
{
    Ov029SceneState *state = data_ov029_020babc0;
    s32 flags = state->flags | 0x4000;

    state->flags = flags;
    return flags;
}
