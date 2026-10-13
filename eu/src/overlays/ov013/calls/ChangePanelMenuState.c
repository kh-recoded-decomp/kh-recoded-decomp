#include "src/overlays/ov013/Ov013PanelState.h"

void ChangePanelMenuState(char nextState)
{
    if (gOv013PanelState->mode != -1) {
        gPanelStateCallbacks[gOv013PanelState->mode].exit();
    }
    gOv013PanelState->mode = nextState;
    gPanelStateCallbacks[gOv013PanelState->mode].enter();
}
