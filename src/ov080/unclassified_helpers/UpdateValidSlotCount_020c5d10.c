#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xd];
    u8 validSlotCount;
} SaveSelectScreen;

extern SaveSelectScreen *data_ov080_020c5e00;

void UpdateValidSlotCount_020c5d10(u32 *slotCount)
{
    if (data_ov080_020c5e00 != NULL && data_ov080_020c5e00->validSlotCount != *slotCount) {
        *slotCount = data_ov080_020c5e00->validSlotCount;
    }
}
