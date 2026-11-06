#include "src/overlays/ov044/PanelState.h"

void *Panel_GetViewState(void)
{
    return &gPanelCameraGlobalStorage->viewState;
}
