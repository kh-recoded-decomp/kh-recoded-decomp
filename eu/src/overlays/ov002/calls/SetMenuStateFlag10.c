#include "src/overlays/ov002/Ov002MenuState.h"

s32 SetMenuStateFlag10(void)
{
    Ov002MenuState *state = gOv002MenuState;
    s32 flags = state->stateFlags | 0x10;

    state->stateFlags = flags;
    return flags;
}
