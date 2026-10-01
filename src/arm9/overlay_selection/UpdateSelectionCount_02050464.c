#include "nitro/types.h"

typedef struct SelectionEntry {
    u8 pad_00[4];
    u8 count;
    u8 pad_05[7];
} SelectionEntry;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x2c];
    SelectionEntry entries[1];
} OverlaySelectionRecord;

extern int FindSlotByActiveOrder_0204f6dc(int targetOrder);
extern int func_02029468(int index);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);

u8 UpdateSelectionCount_02050464(int order)
{
    SelectionEntry *entry;
    int count;
    int slot = FindSlotByActiveOrder_0204f6dc(order);

    if (slot < 0) {
        count = -1;
    } else {
        count = func_02029468(slot);
    }
    entry = &GetOverlaySelectionRecord(0)->entries[order];
    if (count >= 0) {
        entry->count = count;
    } else {
        entry->count--;
    }
    return entry->count;
}
