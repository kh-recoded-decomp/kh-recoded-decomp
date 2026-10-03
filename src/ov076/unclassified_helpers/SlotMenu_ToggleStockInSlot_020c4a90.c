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
    u8 pad_00018[0x3c3c - 0x18];
    ItemStock *stocks[(0x4daa - 0x3c3c) / 4];
    u8 pad_04DA8[2];
    s16 cursorIndex;
    u8 pad_04DAC[0x11ee6 - 0x4dac];
    s16 slotIndex;
    u8 pad_11EE8[0x4a070 - 0x11ee8];
    u32 slotsDirty;
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;

extern void *GetActiveRecordEntryOrNull_02029548(int index);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void SlotMenu_UnequipSlotEntry_020c89e0(SlotMenu *menu, int slot, int column);
extern void SlotMenu_AssignStockToSlot_020c4a38(SlotMenu *menu, ItemStock *stock);

BOOL SlotMenu_ToggleStockInSlot_020c4a90(SlotMenu *menu)
{
    int column = menu->column;
    ItemStock *stock = menu->stocks[menu->cursorIndex];
    int slot = menu->slotIndex;
    u16 handle = data_0205fe0c->slotHandles[slot * 2 + column];

    if (handle == stock->def->handle ||
        (handle >= 0x200 && handle < 0x458 && handle - 0x200 == stock->recordIndex)) {
        if (handle < 0x200) {
            PlaySoundEffect_0204d924(1, 6);
            SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, column);
        } else {
            GetActiveRecordEntryOrNull_02029548((u16)(handle - 0x200));
            PlaySoundEffect_0204d924(1, 6);
            if (column == 0) {
                SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, 1);
            }
            SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, column);
        }
    } else {
        SlotMenu_AssignStockToSlot_020c4a38(menu, stock);
        PlaySoundEffect_0204d924(1, 5);
    }
    menu->slotsDirty = TRUE;
    return TRUE;
}
