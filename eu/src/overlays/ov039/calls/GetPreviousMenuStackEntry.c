#include "src/overlays/ov039/Ov039MenuState.h"

u32 GetPreviousMenuStackEntry(void)
{
    Ov039MenuState *state = gOv039MenuState;

    return state->stackEntries[state->stackDepth - 1];
}
