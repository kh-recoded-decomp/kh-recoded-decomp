#include "nitro/types.h"

/* BG0/BG1 palette slots depend on bit 13 of the engine's BG control register.
 * BG2/BG3 use fixed slots, hence their zero offsets. */
const u16 sBgExtPlttControlOffsets[8] = {
    0x0008, 0x000a, 0, 0, 0x1008, 0x100a, 0, 0,
};
