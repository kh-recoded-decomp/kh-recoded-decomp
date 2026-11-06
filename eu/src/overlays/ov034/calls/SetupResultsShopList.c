#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_0000[0x6d64];
    int itemCount;
    int itemBase;
    int extraPriceA;
    int extraPriceB;
    u8 pad_6d74[0x6d8c - 0x6d74];
    /* Re-read on every pass of the section scan. */
    volatile int shopSection;
} ResultsWork;

typedef struct ResultsScreen {
    void *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct ShopEntry {
    s16 itemId;
    u8 extraPriceA;
    u8 extraPriceB;
    u8 pad_04[8];
} ShopEntry;

extern ResultsScreen gResultsScreenPointersPrefix;
extern ShopEntry gResultsShopEntries[];

/* Find the shop section's first entry (sections end at an itemId of -1), count its items and
 * add the two optional extra prices. */
void SetupResultsShopList(void)
{
    int index = 0;
    int sections = 0;
    ResultsWork *work = gResultsScreenPointersPrefix.work;
    int count;

    while (sections != work->shopSection) {
        if (gResultsShopEntries[index].itemId == -1) {
            sections++;
        }
        index++;
    }
    count = 0;
    work->itemBase = index;
    gResultsScreenPointersPrefix.work->itemCount = 0;
    while (gResultsShopEntries[gResultsScreenPointersPrefix.work->itemBase + count].itemId != -1) {
        count++;
        gResultsScreenPointersPrefix.work->itemCount++;
    }
    gResultsScreenPointersPrefix.work->extraPriceA = gResultsShopEntries[gResultsScreenPointersPrefix.work->itemBase + count].extraPriceA;
    if (gResultsScreenPointersPrefix.work->extraPriceA > 0) {
        gResultsScreenPointersPrefix.work->itemCount++;
    }
    gResultsScreenPointersPrefix.work->extraPriceB = gResultsShopEntries[gResultsScreenPointersPrefix.work->itemBase + count].extraPriceB;
    if (gResultsScreenPointersPrefix.work->extraPriceB > 0) {
        gResultsScreenPointersPrefix.work->itemCount++;
    }
}
