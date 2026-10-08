#include "src/overlays/ov014/Ov014PanelState.h"

void SetPanelInfoMode128(void)
{
    gOv014PanelState->infoMode = 0x80;
}
