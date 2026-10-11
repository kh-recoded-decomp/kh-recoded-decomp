#include "nitro/types.h"

/* D-pad, A/B, X/Y, L/R: input timestamps use the hardware bit index. */
const u16 gKeyRepeatTimestampIndices[10] = { 6, 7, 5, 4, 0, 1, 10, 11, 9, 8 };
const u16 gKeyRepeatButtonMasks[10] = {
    0x0040, 0x0080, 0x0020, 0x0010, 0x0001,
    0x0002, 0x0400, 0x0800, 0x0200, 0x0100
};
