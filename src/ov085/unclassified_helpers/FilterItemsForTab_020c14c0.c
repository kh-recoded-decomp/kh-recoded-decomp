#include "nitro/types.h"

typedef struct KindGroups {
    u32 primary[3];
    u32 secondary[3];
} KindGroups;

typedef struct ItemMenu {
    u8 pad_000[2];
    u8 useCatalog;
    u8 pad_003[9];
    int hasExtraTab;
    u8 pad_010[0x274];
    u8 catalogList[4];
} ItemMenu;

extern KindGroups data_ov085_020c22fc;
extern u16 FilterOwnedEntries_020c1430(ItemMenu *menu, const u32 *kinds, u32 kindCount);
extern u16 FilterEntriesByCategorySet_020c1fa0(void *list, const u32 *categories, u32 categoryCount, BOOL exclude);
extern u16 FilterEntriesByCategory_020c1f8c(void *list, u32 category);

u16 FilterItemsForTab_020c14c0(ItemMenu *menu, int kind)
{
    u32 single;
    KindGroups groups = data_ov085_020c22fc;
    u32 result;

    if (kind == -1) {
        u32 count = 6;

        if (menu->hasExtraTab == 0) {
            count = 3;
        }
        if (menu->useCatalog) {
            result = FilterEntriesByCategorySet_020c1fa0(menu->catalogList, groups.primary, 3, FALSE);
        } else {
            result = FilterOwnedEntries_020c1430(menu, groups.primary, count);
        }
        return result;
    }
    if (kind == -2) {
        return FilterOwnedEntries_020c1430(menu, groups.secondary, 3);
    }
    single = kind;
    if (menu->useCatalog) {
        result = FilterEntriesByCategory_020c1f8c(menu->catalogList, kind);
    } else {
        result = FilterOwnedEntries_020c1430(menu, &single, 1);
    }
    return result;
}
