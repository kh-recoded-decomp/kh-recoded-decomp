#include "src/overlays/ov101/ListSceneState.h"

extern void RuntimeState_SetCondition(int condition);

void ShutdownPageInteractionState(ListSceneState *state)
{
    state->interactionActive = FALSE;
    RuntimeState_SetCondition(FALSE);
}
