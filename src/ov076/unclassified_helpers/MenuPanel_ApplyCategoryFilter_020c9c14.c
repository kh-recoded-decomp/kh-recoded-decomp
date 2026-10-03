#include "nitro/types.h"

typedef struct ItemList {
    u8 pad_0000[0x4580];
    u16 filteredCount;
} ItemList;

typedef struct MenuPanel {
    u8 pad_00000[0x7f8];
    ItemList list;
    u8 pad_0857A[0x11e24 - 0x7f8 - sizeof(ItemList)];
    u8 customCategoryCount;
    u8 pad_11E25[3];
    u32 customCategories[1];
} MenuPanel;

extern const s8 data_ov076_020cd104[];
extern const u32 data_ov076_020cd20c[];

extern u16 ItemList_FilterByCategory_020c95a4(ItemList *list, u32 category);
extern u16 ItemList_FilterByCategorySet_020c95b8(ItemList *list, const u32 *categories, u32 categoryCount, BOOL invert);

void MenuPanel_ApplyCategoryFilter_020c9c14(MenuPanel *panel, int mode)
{
    int category = data_ov076_020cd104[mode];
    const u32 *categories;
    u32 count;

    if (category < 0) {
        if (category == -1) {
            categories = panel->customCategories;
            count = panel->customCategoryCount;
        } else {
            categories = data_ov076_020cd20c;
            count = 3;
        }
        ItemList_FilterByCategorySet_020c95b8(&panel->list, categories, count, FALSE);
        return;
    }
    ItemList_FilterByCategory_020c95a4(&panel->list, category);
}
