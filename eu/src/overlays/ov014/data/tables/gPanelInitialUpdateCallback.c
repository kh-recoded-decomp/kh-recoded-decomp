#include "nitro/types.h"

extern void RefreshOv014SelectedEntryInfo(void);

void (*gPanelInitialUpdateCallback[1])(void) = {
    RefreshOv014SelectedEntryInfo,
};
