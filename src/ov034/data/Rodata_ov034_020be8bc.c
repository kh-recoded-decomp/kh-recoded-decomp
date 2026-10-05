#include "nitro/types.h"

extern void ClearResultsWidgetOnLayer_020bb070(void);
extern void DrawResultsWidgetOnLayer_020bb04c(void);

const u32 data_ov034_020be8e0[9] = {
    0x00001000, 0x00000000, 0x00000000, 0x00000000,
    0x00001000, 0x00000000, 0x00000000, 0x00000000,
    0x00001000,
};

void *const data_ov034_020be8cc[5] = {
    (void *)0x00000007,
    NULL,
    (void *)0x00000007,
    (void *)DrawResultsWidgetOnLayer_020bb04c,
    (void *)ClearResultsWidgetOnLayer_020bb070,
};

const u16 data_ov034_020be8bc[8] = {
    2, 0, 28, 24, 352, 0, 0, 1,
};
