#include "nitro/types.h"

/* Two matrix nodes joined by a link. */
typedef struct GroupPair {
    u8 first;
    u8 second;
} GroupPair;

/* Packed grid cell (x in the low half, y in the high half) the cursor starts on, per matrix level. */
const u32 sMatrixLevelStartCells[8] = {
    0x00600280, 0x00600080, 0x01200280, 0x01200080,
    0x01E00080, 0x01E00280, 0x01E00180, 0x01200180,
};

/* Links of the matrix map, one node pair per link. */
const GroupPair sMatrixNavigationGraph[12] = {
    { 0x00, 0x01 }, { 0x00, 0x02 }, { 0x01, 0x03 }, { 0x02, 0x04 },
    { 0x03, 0x06 }, { 0x04, 0x05 }, { 0x06, 0x07 }, { 0x05, 0x07 },
    { 0x00, 0x08 }, { 0x03, 0x08 }, { 0x04, 0x08 }, { 0x07, 0x08 },
};
