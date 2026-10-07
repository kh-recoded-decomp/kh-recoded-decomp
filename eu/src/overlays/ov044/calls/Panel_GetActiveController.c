#include "src/overlays/ov044/PanelState.h"

void *Panel_GetActiveController(void)
{
    return &data_ov044_020d0ec0->activeController;
}
