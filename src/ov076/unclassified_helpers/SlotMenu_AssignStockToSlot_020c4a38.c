#include "nitro/types.h"

typedef struct ItemDef {
    u32 handle;
    s32 isRecord;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u8 pad_06[2];
    ItemDef *def;
} ItemStock;

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x11ee6 - 0x18];
    s16 slotIndex;
} SlotMenu;

extern void *GetActiveRecordEntryOrNull_02029548(int index);
extern void SlotMenu_UnequipSlotEntry_020c89e0(SlotMenu *menu, int slot, int column);
extern void SlotMenu_EquipSlotEntry_020c8334(SlotMenu *menu, int slot, int column, ItemStock *stock);
extern void SlotMenu_EquipRecordEntry_020c82d8(SlotMenu *menu, int slot, int column, int recordIndex);

void SlotMenu_AssignStockToSlot_020c4a38(SlotMenu *menu, ItemStock *stock)
{
    int slot = menu->slotIndex;
    int column = menu->column;

    if (stock->def->isRecord == 0) {
        SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, 1);
        SlotMenu_EquipSlotEntry_020c8334(menu, slot, 0, stock);
        return;
    }
    if (column == 0) {
        GetActiveRecordEntryOrNull_02029548((u16)stock->recordIndex);
        SlotMenu_EquipRecordEntry_020c82d8(menu, slot, 0, stock->recordIndex);
        return;
    }
    SlotMenu_EquipRecordEntry_020c82d8(menu, slot, 1, stock->recordIndex);
}
