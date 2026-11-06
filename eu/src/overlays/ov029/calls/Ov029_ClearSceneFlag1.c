#include "src/overlays/ov029/Ov029SceneState.h"

s32 Ov029_ClearSceneFlag1(void)
{
    Ov029SceneState *state = gOv029SceneWorkStorage;
    s32 flags = state->flags & 0xfffd;

    state->flags = flags;
    return flags;
}
