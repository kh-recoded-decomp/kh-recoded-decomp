#include "src/overlays/ov015/Ov015PanelWork.h"

void ApplyPendingPanelMode(void)
{
    gOv015PanelWork->mode = gOv015PanelWork->pendingMode;
}
