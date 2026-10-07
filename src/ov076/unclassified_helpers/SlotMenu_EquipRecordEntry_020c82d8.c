#include "nitro/types.h"

#pragma opt_common_subs off

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    s16 slotHandles[16];
} SaveData;

typedef struct ItemInfo {
    u16 pad_00;
    u16 useCount;
    u8 pad_04[8];
} ItemInfo;

typedef struct SlotMenu {
    u8 pad_00000[0x81c];
    ItemInfo items[1];
} SlotMenu;

typedef struct SelectionRecord {
    u8 pad_000[0xec];
    s32 slotAmounts[8];
} SelectionRecord;

extern SaveData *data_0205fe0c;

extern void SlotMenu_UnequipSlotEntry_020c89e0(SlotMenu *menu, int slot, int column);
extern SelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);

static inline void AddItemUse(SlotMenu *menu, u16 handle)
{
    ItemInfo *item = &menu->items[handle];

    item->useCount++;
}

void SlotMenu_EquipRecordEntry_020c82d8(SlotMenu *menu, int slot, int column, s16 recordIndex)
{
    SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, column);
    data_0205fe0c->slotHandles[slot * 2 + column] = recordIndex + 0x200;
    GetOverlaySelectionRecord_0204f768(0)->slotAmounts[slot] = 0;
    AddItemUse(menu, recordIndex + 0x200);
}
