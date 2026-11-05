#include "nitro/types.h"

extern void ItemGrid_HandleState0Noop(void);
extern void EnterPanelState2(void);
extern void UpdateGridScrollDisplay(void);

void (*const gItemReportStateHandlers[3])(void) = {
    ItemGrid_HandleState0Noop,
    EnterPanelState2,
    UpdateGridScrollDisplay,
};
