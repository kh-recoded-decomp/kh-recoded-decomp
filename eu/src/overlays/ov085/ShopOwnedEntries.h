#ifndef SHOP_OWNED_ENTRIES_H
#define SHOP_OWNED_ENTRIES_H

#include "nitro/types.h"

typedef struct OwnedItemCategory {
    u32 reserved00;
    u32 category;
} OwnedItemCategory;

typedef struct OwnedItem {
    u16 total;
    u16 used;
    s16 recordId;
    u16 reserved06;
    OwnedItemCategory *categoryInfo;
} OwnedItem;

typedef struct OwnedEntryOrder {
    u8 reserved00[0xc];
    s32 order;
} OwnedEntryOrder;

typedef struct OwnedItemEntry {
    u8 *count;
    OwnedItem *item;
    OwnedEntryOrder *sortInfo;
} OwnedItemEntry;

typedef struct OwnedItemMenu {
    u8 reserved00[2];
    u8 useCatalog;
    u8 reserved03[9];
    int hasExtraTab;
    u8 reserved10[0x284 - 0x10];
    u8 catalogList[4];
    u8 reserved288[0x4e4c - 0x288];
    OwnedItemEntry ownedEntries[256];
    OwnedItemEntry *filteredEntries[256];
    u32 ownedCount;
    u32 filteredCount;
} OwnedItemMenu;

int CompareOwnedItemOrder(const void *first, const void *second);
u16 FilterOwnedEntries(OwnedItemMenu *menu, const u32 *categories, u32 categoryCount);

#endif
