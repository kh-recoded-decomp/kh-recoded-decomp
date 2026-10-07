#include "src/overlays/ov002/Ov002PanelState.h"

s32 SetPanelStateFlag4(void)
{
    Ov002PanelState *state = gOv002PanelState;
    s32 flags = state->stateFlags | 4;

    state->stateFlags = flags;
    return flags;
}
