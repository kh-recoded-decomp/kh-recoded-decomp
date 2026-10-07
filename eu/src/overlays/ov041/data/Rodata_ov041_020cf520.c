#include "nitro/types.h"

typedef struct Ov041AnimationSelectorTable {
    u8 selectorOrder[4];
    u32 selectorMasks[3];
} Ov041AnimationSelectorTable;

const Ov041AnimationSelectorTable data_ov041_020cf520 = {
    { 0x00, 0x01, 0x02, 0x03 },
    { 0x02010004, 0x01000403, 0x00040302 },
};
