#include "src/overlays/ov044/PanelState.h"

VecFx32 *Panel_GetDriftOrigin(void)
{
    return &gPanelCameraGlobalStorage->driftOrigin;
}
