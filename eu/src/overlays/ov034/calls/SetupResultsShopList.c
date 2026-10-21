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

extern ResultsScreen data_ov034_020c0fa0;
extern ShopEntry gResultsShopEntries[];

/* Find the shop section's first entry (sections end at an itemId of -1), count its items and
 * add the two optional extra prices. */
void SetupResultsShopList(void)
{
    int index = 0;
    int sections = 0;
    ResultsWork *work = data_ov034_020c0fa0.work;
    int count;

    while (sections != work->shopSection) {
        if (gResultsShopEntries[index].itemId == -1) {
            sections++;
        }
        index++;
    }
    count = 0;
    work->itemBase = index;
    data_ov034_020c0fa0.work->itemCount = 0;
    while (gResultsShopEntries[data_ov034_020c0fa0.work->itemBase + count].itemId != -1) {
        count++;
        data_ov034_020c0fa0.work->itemCount++;
    }
    data_ov034_020c0fa0.work->extraPriceA = gResultsShopEntries[data_ov034_020c0fa0.work->itemBase + count].extraPriceA;
    if (data_ov034_020c0fa0.work->extraPriceA > 0) {
        data_ov034_020c0fa0.work->itemCount++;
    }
    data_ov034_020c0fa0.work->extraPriceB = gResultsShopEntries[data_ov034_020c0fa0.work->itemBase + count].extraPriceB;
    if (data_ov034_020c0fa0.work->extraPriceB > 0) {
        data_ov034_020c0fa0.work->itemCount++;
    }
}
