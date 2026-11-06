#include "src/overlays/ov001/panel_state.h"

void RequestPanelBrightnessRestore(void)
{
    gSubscenePanelWork->brightnessRestoreRequested = TRUE;
}
