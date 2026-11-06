#include "nitro/types.h"

extern void DrawMenuEntryWidget(void);
extern void DrawMenuWidgetGraphic(void);
extern void MakePrimaryVramKey_02071214(void);
extern void RefreshRemainingCount(void);

void *const gPanelListViewConfig[12] = {
    (void *)MakePrimaryVramKey_02071214,
    (void *)RefreshRemainingCount,
    NULL,
    (void *)0x00000001,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

void *const gPanelListBackgroundContainerConfig[5] = {
    (void *)0x00000002,
    NULL,
    (void *)0x00000002,
    (void *)DrawMenuWidgetGraphic,
    (void *)DrawMenuEntryWidget,
};

const u16 gPanelListTextLayerConfig[8] = {
    16, 0, 16, 2, 384, 15, 0, 0,
};
