#include "nitro/types.h"

typedef struct ItemList {
    u8 pad_0000[0x4580];
    u16 filteredCount;
} ItemList;

extern void func_ov076_020c93f8(ItemList *list, const u32 *categories, u32 categoryCount, BOOL invert);

u16 ItemList_FilterByCategorySet_020c95b8(ItemList *list, const u32 *categories, u32 categoryCount, BOOL invert)
{
    func_ov076_020c93f8(list, categories, categoryCount, invert);
    return list->filteredCount;
}
