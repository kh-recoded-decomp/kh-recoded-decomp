#include "nitro/types.h"

typedef struct ResultsParams {
    int money;
} ResultsParams;

typedef struct ResultsWork {
    u8 pad_0000[0x6b3c];
    u8 messages[0x22c];
    int itemBase;
    int extraPriceA;
    int extraPriceB;
} ResultsWork;

typedef struct ItemInfo {
    u8 pad_00[0x10];
    int iconId;
    u8 pad_14[0x2c];
    const u16 *name;
    const u16 *description;
} ItemInfo;

typedef struct ResultsScreen {
    ResultsParams *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct ShopEntry {
    s16 itemId;
    u8 pad_02[10];
} ShopEntry;

extern ResultsScreen g_resultsScreen_020c0f80;
extern u16 g_resultsExtraName_020c0f88[0x20];
extern ItemInfo g_resultsExtraInfo_020c0fc8;
extern ShopEntry data_ov034_020bed4c[];

extern int ClassifyResultsShopEntry_020be4f8(int itemIndex);
extern ItemInfo *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern const u16 *func_ov027_020ba2a8(void *messages, int index);
extern void OS_SNPrintf_0202e080(u16 *buffer, u32 size, const u16 *format, ...);

static inline int CalcExtraPrice(int *percent)
{
    int price = (g_resultsScreen_020c0f80.params->money * *percent + 99) / 100;

    if (price > 99999) {
        price = 99999;
    }
    return price;
}

ItemInfo *GetResultsShopItemInfo_020be418(int itemIndex)
{
    int kind;
    int price;

    kind = ClassifyResultsShopEntry_020be4f8(itemIndex);
    if (kind == 0) {
        return GetRecordSlotPair0Entry_02051ec8(data_ov034_020bed4c[g_resultsScreen_020c0f80.work->itemBase + itemIndex].itemId);
    }
    if (kind == 2) {
        price = CalcExtraPrice(&g_resultsScreen_020c0f80.work->extraPriceA);
        OS_SNPrintf_0202e080(g_resultsExtraName_020c0f88, 0x20, func_ov027_020ba2a8(g_resultsScreen_020c0f80.work->messages, 0x25), price);
        g_resultsExtraInfo_020c0fc8.iconId = -1;
        g_resultsExtraInfo_020c0fc8.description = func_ov027_020ba2a8(g_resultsScreen_020c0f80.work->messages, 0x26);
    } else {
        price = CalcExtraPrice(&g_resultsScreen_020c0f80.work->extraPriceB);
        OS_SNPrintf_0202e080(g_resultsExtraName_020c0f88, 0x20, func_ov027_020ba2a8(g_resultsScreen_020c0f80.work->messages, 0x27), price);
        g_resultsExtraInfo_020c0fc8.iconId = -1;
        g_resultsExtraInfo_020c0fc8.description = func_ov027_020ba2a8(g_resultsScreen_020c0f80.work->messages, 0x28);
    }
    g_resultsExtraInfo_020c0fc8.name = g_resultsExtraName_020c0f88;
    return &g_resultsExtraInfo_020c0fc8;
}
