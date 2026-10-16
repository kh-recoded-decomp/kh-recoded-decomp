#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct ItemDef {
    u32 handle;
    u32 category;
    u8 unknown08[0x10];
    u16 sortKey;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u8 unknown06[2];
    ItemDef *def;
} ItemStock;

typedef struct ItemList {
    ItemStock stocks[0x200];
    ItemStock records[600];
    ItemStock *filtered[0x458];
    u16 filteredCount;
    u8 ready;
    u8 unknown4583;
    u32 categoryMask;
} ItemList;

typedef char RecordEntryIsFourBytes[sizeof(RecordEntry) == 4 ? 1 : -1];
typedef char ItemStockIs12Bytes[sizeof(ItemStock) == 12 ? 1 : -1];
typedef char ItemSortKeyOffset[(u32)&((ItemDef *)0)->sortKey == 0x18 ? 1 : -1];
typedef char ItemStockDefOffset[(u32)&((ItemStock *)0)->def == 8 ? 1 : -1];
typedef char ItemListRecordsOffset[(u32)&((ItemList *)0)->records == 0x1800 ? 1 : -1];
typedef char ItemListFilteredOffset[(u32)&((ItemList *)0)->filtered == 0x3420 ? 1 : -1];
typedef char ItemListCountOffset[(u32)&((ItemList *)0)->filteredCount == 0x4580 ? 1 : -1];
typedef char ItemListReadyOffset[(u32)&((ItemList *)0)->ready == 0x4582 ? 1 : -1];
typedef char ItemListMaskOffset[(u32)&((ItemList *)0)->categoryMask == 0x4584 ? 1 : -1];

extern void InitItemListEntries(ItemList *list);
extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern void qsort(void *base, u32 count, u32 width,
    int (*compare)(const void *left, const void *right));
extern int ItemList_CompareStock_020c5f84(const void *left, const void *right);

/* Rebuild and sort the visible stock pointers for the selected category filter. */
void ItemList_ApplyCategoryFilter_020c644c(ItemList *list, const u32 *categories, u32 categoryCount, BOOL invert)
{
    ItemStock **out = list->filtered;
    u32 categoryMask = 0;

    if (!list->ready) {
        InitItemListEntries(list);
    }
    if (categoryCount == 0) {
        ItemStock *stock = list->records;
        u32 recordMask = 12;
        if (invert) {
            recordMask = ~recordMask;
        }
        list->filteredCount = 0;
        for (u32 index = 0; index < 600; ++index, ++stock) {
            RecordEntry *record = GetActiveRecordEntryOrNull((u16)index);
            if (record != NULL && stock->def->sortKey < 9999 && stock->total != 0) {
                u16 category = (u16)record->category;
                u16 entryStride = sizeof(ItemStock);
                category = (u8)category;
                int byteOffset = entryStride * category;
                ItemStock *baseStock = (ItemStock *)((u8 *)list->stocks + byteOffset);
                if ((recordMask & (1u << baseStock->def->category)) && record->variant != 0) {
                    *out++ = stock;
                    ++list->filteredCount;
                }
            }
        }
        qsort(list->filtered, list->filteredCount, sizeof(ItemStock *), ItemList_CompareStock_020c5f84);
        return;
    }
    for (u32 index = 0; index < categoryCount; ++index) {
        categoryMask |= 1u << categories[index];
    }
    if (invert) {
        categoryMask = ~categoryMask;
    }
    list->filteredCount = 0;
    if (list->categoryMask & categoryMask) {
        if (categoryMask & ~12u) {
            ItemStock *stock = list->stocks;
            for (u32 index = 0; index < 0x200; ++index, ++stock) {
                if (index > 0x7f && stock->total != 0 && stock->def->sortKey < 9999 &&
                    ((1u << stock->def->category) & categoryMask)) {
                    *out++ = stock;
                    ++list->filteredCount;
                }
            }
        }
        if (categoryMask & 12) {
            ItemStock *stock = list->records;
            for (u32 index = 0; index < 600; ++index, ++stock) {
                RecordEntry *record = GetActiveRecordEntryOrNull((u16)index);
                if (record != NULL && stock->def->sortKey < 9999 && stock->total != 0) {
                    u16 category = (u16)record->category;
                    u16 entryStride = sizeof(ItemStock);
                    category = (u8)category;
                    int byteOffset = entryStride * category;
                    ItemStock *baseStock = (ItemStock *)((u8 *)list->stocks + byteOffset);
                    if (categoryMask & (1u << baseStock->def->category)) {
                        *out++ = stock;
                        ++list->filteredCount;
                    }
                }
            }
        }
        qsort(list->filtered, list->filteredCount, sizeof(ItemStock *), ItemList_CompareStock_020c5f84);
    }
}
