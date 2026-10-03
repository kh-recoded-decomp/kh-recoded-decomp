#include "nitro/types.h"

typedef struct ItemList {
    u8 data[0x4580];
} ItemList;

typedef struct ItemMenu {
    u8 pad_00000[0x7f8];
    ItemList list;
    u8 pad_04d78[0x11e24 - 0x4d78];
    u8 customCount;
    u8 pad_11e25[3];
    u32 customCategories[1];
} ItemMenu;

extern const s8 data_ov075_020d1658[];
extern const u32 data_ov075_020d1784[];
extern u16 BuildCategoryList_020cd35c(ItemList *list, u32 category);
extern u16 BuildCategorySetList_020cd370(ItemList *list, const u32 *categories, u32 categoryCount, BOOL exclude);

void BuildTabItemList_020cde04(ItemMenu *menu, int tab)
{
    s8 category = data_ov075_020d1658[tab];
    const u32 *categories;
    u32 count;

    if (category < 0) {
        if (category == -1) {
            categories = menu->customCategories;
            count = menu->customCount;
        } else {
            categories = data_ov075_020d1784;
            count = 3;
        }
        BuildCategorySetList_020cd370(&menu->list, categories, count, FALSE);
        return;
    }
    BuildCategoryList_020cd35c(&menu->list, category);
}