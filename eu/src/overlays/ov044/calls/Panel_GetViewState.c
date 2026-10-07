#include "src/overlays/ov044/PanelState.h"

void *Panel_GetViewState(void)
{
    return &data_ov044_020d0ec0->viewState;
}
