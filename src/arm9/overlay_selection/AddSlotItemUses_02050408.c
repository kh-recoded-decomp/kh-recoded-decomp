#include "nitro/types.h"

typedef struct SelectionSlot {
    u8 pad_00[4];
    u8 uses;
    u8 pad_05[7];
} SelectionSlot;

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0x2b];
    SelectionSlot slots[1];
} OverlaySelectionRecord;

extern int FindSlotByActiveOrder_0204f6dc(int targetOrder);
extern u16 RefillSlotItemUses_020294b8(int index);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);

int AddSlotItemUses_02050408(int order)
{
    int slot = FindSlotByActiveOrder_0204f6dc(order);
    int amount;

    if (slot < 0) {
        amount = -1;
    } else {
        amount = (s16)RefillSlotItemUses_020294b8(slot);
    }
    if (amount > 0) {
        SelectionSlot *entry = &GetOverlaySelectionRecord_0204f768(0)->slots[order];
        entry->uses += (u8)amount;
        amount = entry->uses;
    }
    return amount;
}
