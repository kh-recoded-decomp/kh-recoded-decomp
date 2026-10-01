#include "nitro/types.h"

typedef struct ShopState {
    u8 pad_000[0x109];
    u8 itemCount;
    u8 itemIds[0x16];
    u8 prices[0x16];
} ShopState;

extern ShopState *data_ov001_020a0470;
extern void func_01ff8830(void *dst, int value, u32 size);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern s32 GetShortTableValueOrDefault_020521dc(s32 index);

void BuildUniqueItemPriceList_02068604(u16 *ids, int count)
{
    ShopState *shop = data_ov001_020a0470;
    int i;
    int j;

    shop->itemCount = 0;
    func_01ff8830(shop->itemIds, 0xff, 0x16);
    for (i = 0; i < count; i++) {
        BOOL found = FALSE;
        for (j = 0; j < shop->itemCount; j++) {
            if (shop->itemIds[j] == ids[i]) {
                found = TRUE;
                break;
            }
        }
        if (!found) {
            shop->itemIds[shop->itemCount] = ids[i];
            shop->itemCount++;
        }
    }
    func_01ff8830(shop->prices, 0x28, 0x16);
    AcquireRecordSlot_02051d3c(7, 1);
    for (i = 0; i < shop->itemCount; i++) {
        shop->prices[i] = GetShortTableValueOrDefault_020521dc(shop->itemIds[i]);
    }
    ReleaseRecordSlot_02051dfc(7);
}
