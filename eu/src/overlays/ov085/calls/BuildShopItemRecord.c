#pragma opt_propagation off
#include "nitro/types.h"

typedef union RecordEntry {
    struct {
        u16 rank : 2;
        u16 state : 3;
        u16 levelProgress : 11;
        u16 active : 1;
        u16 level : 7;
        u16 category : 8;
    };
    u16 words[2];
} RecordEntry;

typedef struct ItemEntry {
    u16 total;
    u16 used;
    s16 recordId;
    u16 pad_06;
    void *info;
} ItemEntry;

typedef struct ShopItemDefinition {
    int itemId;
    u8 unk04;
    u8 level;
    s8 rank;
    u8 maxLevel;
    u32 price;
} ShopItemDefinition;

typedef struct OwnedEntry {
    u8 *count;
    ItemEntry *entry;
    ShopItemDefinition *definition;
} OwnedEntry;

typedef struct ShopMenu {
    u8 pad_00[2];
    u8 useCatalog;
    u8 pad_03[0x36a4 - 3];
    ItemEntry *catalog[0x45b];
    u8 images[0x123c];
    OwnedEntry *slots[0x102];
} ShopMenu;

extern RecordEntry *GetActiveRecordEntryOrNull(u16 index);

/* Copy an existing catalog record, or assemble one from the owned-slot definition. */
BOOL BuildShopItemRecord(ShopMenu *menu, u32 index, RecordEntry *out)
{
    if (menu->useCatalog) {
        s16 recordId = menu->catalog[(u16)index]->recordId;
        if (recordId >= 0) {
            RecordEntry *entry = GetActiveRecordEntryOrNull((u16)recordId);
            out->words[0] = entry->words[0];
            out->words[1] = entry->words[1];
            return TRUE;
        }
    } else {
        ShopItemDefinition *item = menu->slots[index]->definition;
        if (item->itemId >= 0 && item->itemId <= 0x7f) {
            u32 category;
            out->level = item->level;
            out->rank = (u16)(item->rank + 1);
            out->state = 0;
            category = item->itemId;
            out->category = (u8)category;
            return TRUE;
        }
    }
    return FALSE;
}
