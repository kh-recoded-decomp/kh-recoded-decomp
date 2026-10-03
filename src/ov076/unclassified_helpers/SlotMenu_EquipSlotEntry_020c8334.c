#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
    u8 pad_2DA4[0x2dc0 - 0x2da4];
    s32 slotAmounts[8];
} SaveData;

typedef struct ItemDef {
    u32 handle;
    u8 pad_04[0x20];
    s32 maxPerSlot;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    u8 pad_04[4];
    ItemDef *def;
} ItemStock;

extern SaveData *data_0205fe0c;

extern void SlotMenu_UnequipSlotEntry_020c89e0(void *menu, int slot, int column);

void SlotMenu_EquipSlotEntry_020c8334(void *menu, int slot, int column, ItemStock *stock)
{
    int amount;
    int limit;

    SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, column);
    data_0205fe0c->slotHandles[slot * 2 + column] = stock->def->handle;
    limit = stock->def->maxPerSlot;
    amount = stock->total - stock->used;
    if (amount > limit) {
        amount = limit;
    }
    stock->used += amount;
    data_0205fe0c->slotAmounts[slot] = amount;
}
