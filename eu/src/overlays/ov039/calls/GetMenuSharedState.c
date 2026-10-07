#include "src/overlays/ov039/Ov039MenuState.h"

void *GetMenuSharedState(void)
{
    return gOv039MenuState->sharedState;
}
