#include "src/overlays/ov001/panel_state.h"

void RequestPanelFallback(void)
{
    gSubscenePanelWork->fallbackRequested = TRUE;
}
