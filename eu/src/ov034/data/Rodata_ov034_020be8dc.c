#include "nitro/types.h"

extern void ClearResultsWidgetOnLayer(void);
extern void DrawResultsWidgetOnLayer(void);

const u32 data_ov034_020be900[9] = {
    0x00001000, 0x00000000, 0x00000000, 0x00000000,
    0x00001000, 0x00000000, 0x00000000, 0x00000000,
    0x00001000,
};

void *const data_ov034_020be8ec[5] = {
    (void *)0x00000007,
    NULL,
    (void *)0x00000007,
    (void *)DrawResultsWidgetOnLayer,
    (void *)ClearResultsWidgetOnLayer,
};

const u16 data_ov034_020be8dc[8] = {
    2, 0, 28, 24, 352, 0, 0, 1,
};
