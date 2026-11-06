#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x28d7];
    u8 slotTotal : 4;
    u8 slotFilled : 4;
} SaveData;

typedef struct SlotEntry {
    u8 pad_00[4];
    void *item;
    u8 pad_08[8];
} SlotEntry;

extern SaveData *gSaveIoStateDataTail;

void UpdateSlotFillCounts(SlotEntry *slots, int count)
{
    int filled;
    int i;

    gSaveIoStateDataTail->slotTotal = count;
    i = count - 1;
    filled = 0;
    for (; i >= 0; i--) {
        if (slots[i].item != NULL) {
            filled++;
        }
    }
    gSaveIoStateDataTail->slotFilled = filled;
}
