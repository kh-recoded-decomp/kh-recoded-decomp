#include "nitro/types.h"

extern void DrawMenuEntryWidget(void);
extern void DrawMenuWidgetGraphic(void);
extern void MakePrimaryVramKey_02071214(void);
extern void RefreshRemainingCount(void);

void *const data_ov025_020b76f4[12] = {
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

void *const data_ov025_020b76e0[5] = {
    (void *)0x00000002,
    NULL,
    (void *)0x00000002,
    (void *)DrawMenuWidgetGraphic,
    (void *)DrawMenuEntryWidget,
};

const u16 data_ov025_020b76d0[8] = {
    16, 0, 16, 2, 384, 15, 0, 0,
};
