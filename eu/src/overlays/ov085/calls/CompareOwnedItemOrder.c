#include "src/overlays/ov085/ShopOwnedEntries.h"

int CompareOwnedItemOrder(const void *first, const void *second)
{
    const OwnedItemEntry *a = *(const OwnedItemEntry *const *)first;
    const OwnedItemEntry *b = *(const OwnedItemEntry *const *)second;

    return a->sortInfo->order - b->sortInfo->order;
}
