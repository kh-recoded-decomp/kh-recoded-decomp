#include "src/overlays/ov085/ShopOwnedEntries.h"

typedef struct KindGroups {
    u32 primary[3];
    u32 secondary[3];
} KindGroups;

extern KindGroups data_ov085_020c231c;
extern u16 FilterEntriesByCategorySet(void *list, const u32 *categories,
                                     u32 categoryCount, BOOL exclude);
extern u16 FilterEntriesByCategory(void *list, u32 category);

u16 FilterItemsForTab(OwnedItemMenu *menu, int kind)
{
    u32 single;
    KindGroups groups = data_ov085_020c231c;
    u32 result;

    if (kind == -1) {
        u32 count = 6;

        if (menu->hasExtraTab == 0) {
            count = 3;
        }
        if (menu->useCatalog) {
            result = FilterEntriesByCategorySet(menu->catalogList, groups.primary, 3, FALSE);
        } else {
            result = FilterOwnedEntries(menu, groups.primary, count);
        }
        return result;
    }
    if (kind == -2) {
        return FilterOwnedEntries(menu, groups.secondary, 3);
    }
    single = kind;
    if (menu->useCatalog) {
        result = FilterEntriesByCategory(menu->catalogList, kind);
    } else {
        result = FilterOwnedEntries(menu, &single, 1);
    }
    return result;
}
