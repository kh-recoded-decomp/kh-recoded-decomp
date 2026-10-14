#include "src/overlays/ov085/ShopOwnedEntries.h"

extern void qsort(void *base, u32 count, u32 size,
                  int (*compare)(const void *, const void *));

/* Build and sort the owned-item view for the selected category set. */
u16 FilterOwnedEntries(OwnedItemMenu *menu, const u32 *categories, u32 categoryCount)
{
    OwnedItemEntry *entry = menu->ownedEntries;
    u8 *output = (u8 *)menu->filteredEntries;
    u32 categoryMask = 0;
    u32 filteredCount = 0;
    u32 index;

    for (index = 0; index < categoryCount; index++) {
        categoryMask |= 1UL << categories[index];
    }
    for (index = 0; index < menu->ownedCount; index++, entry++) {
        if ((1UL << entry->item->categoryInfo->category) & categoryMask) {
            /* The cursor advances by one pointer-sized output slot. */
            *(OwnedItemEntry **)output = entry;
            output += sizeof(OwnedItemEntry *);
            filteredCount++;
        }
    }
    if (filteredCount > 1) {
        qsort(menu->filteredEntries, filteredCount, sizeof(OwnedItemEntry *),
              CompareOwnedItemOrder);
    }
    menu->filteredCount = filteredCount;
    return filteredCount;
}
