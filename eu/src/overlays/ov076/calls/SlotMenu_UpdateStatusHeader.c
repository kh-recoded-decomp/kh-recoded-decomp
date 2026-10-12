#include "nitro/types.h"

typedef struct SlotHeaderItemDef {
    s32 handle;
    BOOL isRecord;
    u8 reserved08[0x18];
    s32 recordId;
    u8 reserved24[0x1c];
    const u16 *name;
    const u16 *description;
} SlotHeaderItemDef;

typedef struct SlotHeaderStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u16 reserved06;
    SlotHeaderItemDef *def;
} SlotHeaderStock;

typedef struct SlotHeaderSelection {
    u16 slotFlags : 8;
    u16 stockIndex : 8;
    u16 reserved02;
} SlotHeaderSelection;

typedef struct SlotHeaderMenu {
    u8 reserved00000[0x14];
    s32 column;
    u8 reserved00018[0xc];
    u8 itemList[0x81c - 0x24];
    SlotHeaderStock stocks[0x458];
    u8 reserved03c3c[0x11ee6 - 0x3c3c];
    s16 slotIndex;
    u8 reserved11ee8[0x497fa - 0x11ee8];
    SlotHeaderSelection selections[8];
} SlotHeaderMenu;

typedef struct SlotHeaderSave {
    u8 reserved0000[0x2d84];
    /* Two equipped IDs for each slot. */
    u16 equippedSlots[16];
} SlotHeaderSave;

typedef struct SlotHeaderCommandRecord {
    u8 reserved00[0x1e];
    s16 level;
} SlotHeaderCommandRecord;

extern SlotHeaderSave *data_0205fe0c;
extern void *GetActiveRecordEntryOrNull(int index);
extern SlotHeaderStock *CommandMatrix_GetStockForRecord(void *menu, const void *record);
extern SlotHeaderCommandRecord *GetRecordSlotPair1Entry(s32 index);
extern void SetStatusHeaderMessage(const u16 *name, const u16 *description, int kind, int value);
extern void SetStatusHeaderText(const u16 *name, const u16 *description);

#pragma opt_propagation off
void SlotMenu_UpdateStatusHeader(SlotHeaderMenu *menu)
{
    SlotHeaderStock *stock = NULL;
    int slot = menu->slotIndex;

    if (menu->column == 2) {
        u16 id = data_0205fe0c->equippedSlots[slot * 2];
        if (id >= 0x200 && id < 0x458) {
            u8 stockIndex = menu->selections[slot].stockIndex;
            stock = &menu->stocks[stockIndex];
        } else if (id < 0x200) {
            stock = &menu->stocks[id];
        }
    } else {
        u16 id = data_0205fe0c->equippedSlots[slot * 2 + menu->column];
        if (id >= 0x200 && id < 0x458) {
            stock = &menu->stocks[id];
            if (stock->recordIndex >= 0) {
                stock = CommandMatrix_GetStockForRecord(menu->itemList,
                    GetActiveRecordEntryOrNull((u16)stock->recordIndex));
            }
        } else if (id < 0x200) {
            stock = &menu->stocks[id];
        }
    }
    if (stock != NULL) {
        SlotHeaderCommandRecord *record = GetRecordSlotPair1Entry(stock->def->recordId);
        SetStatusHeaderMessage(stock->def->name, stock->def->description, 1, record->level);
    } else {
        SetStatusHeaderText(NULL, NULL);
    }
}
#pragma opt_propagation on
