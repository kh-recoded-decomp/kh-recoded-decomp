#include "nitro/types.h"

typedef struct ItemList {
    u8 pad_0000[0x4580];
    u16 filteredCount;
} ItemList;

extern void func_ov076_020c92e8(ItemList *list, u32 category);

u16 ItemList_FilterByCategory_020c95a4(ItemList *list, u32 category)
{
    func_ov076_020c92e8(list, category);
    return list->filteredCount;
}
