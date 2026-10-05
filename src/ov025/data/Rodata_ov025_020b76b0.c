#include "nitro/types.h"

extern void DrawMenuEntryWidget_020b59d8(void);
extern void DrawMenuWidgetGraphic_020b597c(void);
extern void MakePrimaryVramKey_02071214(void);
extern void RefreshRemainingCount_020b58d8(void);

void *const data_ov025_020b76d4[12] = {
    (void *)MakePrimaryVramKey_02071214,
    (void *)RefreshRemainingCount_020b58d8,
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

void *const data_ov025_020b76c0[5] = {
    (void *)0x00000002,
    NULL,
    (void *)0x00000002,
    (void *)DrawMenuWidgetGraphic_020b597c,
    (void *)DrawMenuEntryWidget_020b59d8,
};

const u16 data_ov025_020b76b0[8] = {
    16, 0, 16, 2, 384, 15, 0, 0,
};
