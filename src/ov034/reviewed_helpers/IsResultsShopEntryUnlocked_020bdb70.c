#include "nitro/types.h"

typedef struct ResultsParams {
    u8 pad_00[0x24];
    u8 unlockedRank;
    u8 maxRank;
} ResultsParams;

typedef struct ResultsWork {
    u8 pad_0000[0x6d68];
    int shopBase;
} ResultsWork;

typedef struct ResultsScreen {
    ResultsParams *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct ShopEntry {
    u8 pad_00[9];
    s8 requiredRank;
    u8 pad_0a[2];
} ShopEntry;

extern ResultsScreen g_resultsScreen_020c0f80;
extern ShopEntry data_ov034_020bed4c[];
extern void func_ov034_020be418(int index);
extern int ClassifyResultsShopEntry_020be4f8(int index);

BOOL IsResultsShopEntryUnlocked_020bdb70(int index)
{
    ShopEntry *entry;
    int rank;

    func_ov034_020be418(index);
    entry = &data_ov034_020bed4c[g_resultsScreen_020c0f80.work->shopBase + index];
    if (ClassifyResultsShopEntry_020be4f8(index) != 0 ||
        ((rank = entry->requiredRank) >= 0 && rank <= g_resultsScreen_020c0f80.params->unlockedRank) ||
        (rank < 0 && g_resultsScreen_020c0f80.params->unlockedRank == g_resultsScreen_020c0f80.params->maxRank)) {
        return TRUE;
    }
    return FALSE;
}
