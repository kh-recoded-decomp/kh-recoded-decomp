#include "src/overlays/ov044/PanelState.h"

VecFx32 *Panel_GetDriftOrigin(void)
{
    return &data_ov044_020d0ec0->driftOrigin;
}
