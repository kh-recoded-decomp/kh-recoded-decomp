#include "nitro/types.h"

typedef struct RewardAmounts {
    u16 firstOrb;
    u16 secondOrb;
    u16 otherOrbs[4];
} RewardAmounts;

typedef struct SpecialDropRow {
    u16 orbWeights[3];
    u16 itemWeights[7];
    u16 orbAmounts[2];
} SpecialDropRow;

typedef struct SpecialDrops {
    u8 pad_00[0x64];
    SpecialDropRow rows[8];
    u16 itemIds[7];
} SpecialDrops;

enum { RANDOM_SPECIAL_ITEM = 0x87, ITEM_EFFECT_KIND = 6 };

typedef char SpecialDropRowSizeCheck[(sizeof(SpecialDropRow) == 0x18) ? 1 : -1];

extern SpecialDrops *data_ov001_020a04fc;
extern s8 GetCtxModeByte(void);
extern u32 func_0202a9e4(u32 range);
extern void SpawnRewardOrbs(RewardAmounts *amounts, void *target, int mode);
extern u32 func_ov001_020664f0(u32 kind, u32 size, void *target, u32 mode);

static inline void ClearRewardAmounts(RewardAmounts *reward)
{
    u16 *amounts = (u16 *)reward;

    amounts[0] = 0;
    amounts[1] = 0;
    amounts[2] = 0;
    amounts[3] = 0;
    amounts[4] = 0;
    amounts[5] = 0;
}

void RollSpecialItemDrop(int itemId, void *target)
{
    SpecialDrops *drops = data_ov001_020a04fc;
    SpecialDropRow *row;
    RewardAmounts amounts;
    u16 first, second, cumulative;
    u32 roll;
    u16 orb0, orb1;
    int i;

    if (itemId == RANDOM_SPECIAL_ITEM) {
        row = &drops->rows[GetCtxModeByte()];
        roll = func_0202a9e4(10000);
        first = row->orbWeights[0];
        second = first + row->orbWeights[1];
        cumulative = second + row->orbWeights[2];
        orb0 = 0;
        orb1 = 0;
        if (roll < first) {
            orb0 = row->orbAmounts[0];
        } else if (roll < second) {
            orb1 = row->orbAmounts[1];
        } else if (roll < cumulative) {
            orb0 = row->orbAmounts[0];
            orb1 = row->orbAmounts[1];
        }
        if (orb0 != 0 || orb1 != 0) {
            ClearRewardAmounts(&amounts);
            amounts.firstOrb = orb0;
            amounts.secondOrb = orb1;
            SpawnRewardOrbs(&amounts, target, 0);
            return;
        }
        for (i = 0; i < 7; i++) {
            cumulative += row->itemWeights[i];
            if (roll < cumulative) {
                func_ov001_020664f0(ITEM_EFFECT_KIND, drops->itemIds[i], target, 0);
                return;
            }
        }
    } else {
        func_ov001_020664f0(ITEM_EFFECT_KIND, itemId, target, 0);
    }
}
