#include "src/overlays/ov044/PanelState.h"

void *Panel_GetActiveController(void)
{
    return &gPanelCameraGlobalStorage->activeController;
}
