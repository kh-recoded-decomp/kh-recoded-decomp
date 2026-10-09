#include "nitro/types.h"

typedef struct Ov041AnimationTrackTable {
    u8 header[4];
    u8 count;
    u8 entries[11];
} Ov041AnimationTrackTable;

const Ov041AnimationTrackTable gSpecialStageItem1ColorTable = {
    { 0xFF, 0x02, 0x00, 0xFF },
    0x03,
    { 0x00, 0xFF, 0x04, 0x00, 0xFF, 0x04, 0x01, 0xFF, 0x15, 0x00, 0xFF },
};
