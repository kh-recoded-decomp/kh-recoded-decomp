#include "nitro/types.h"

/* Offsets into PanelState.entryStorage, one for each category. */
const u16 gPanelGroupEntryOffsets[20] = {
    0x000, 0x005, 0x00a, 0x02b, 0x0b5, 0x0c4, 0x0cf, 0x0e1,
    0x122, 0x165, 0x1aa, 0x203, 0x23d, 0x26b, 0x29f, 0x2a7,
    0x2ac, 0x30c, 0x32f, 0x31d,
};

/* Category ids displayed in each row of the four-group panel. */
const u8 gPanelGroupCategories[4][7] = {
    { 0, 1, 2, 3, 4, 5, 0 },
    { 6, 7, 8, 9, 10, 0, 0 },
    { 11, 12, 13, 14, 15, 16, 19 },
    { 17, 18, 0, 0, 0, 0, 0 },
};

const u8 gPanelCategoryEntryCounts[20] = {
    5, 5, 33, 138, 15, 11, 18, 65, 67, 69,
    89, 58, 46, 52, 8, 5, 96, 17, 93, 18,
};

const u16 data_ov014_0206f800[4] = { 207, 308, 283, 110 };

const u8 gPanelGroupWidths[4] = { 6, 5, 7, 2 };
