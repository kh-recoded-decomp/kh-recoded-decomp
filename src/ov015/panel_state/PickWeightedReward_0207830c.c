#include "nitro/types.h"

typedef struct {
    s16 type;
    s16 id;
    u16 level;
    u16 kind;
    u8 weight;
    u8 pad_09[3];
} Reward;

typedef struct {
    Reward entries[5];
} RewardTier;

typedef struct {
    RewardTier **lists[7];
} RewardTableSet;

typedef struct {
    u8 pad_00[0x50];
    s8 stage;
} PanelProgress;

extern const RewardTableSet data_ov015_0207e868;
extern PanelProgress *data_ov015_020812e0;
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern int GetPanelPageCount_020779dc(void);
extern unsigned int func_0202a9d0(u16 range);
extern BOOL GrantRewardEntry_02078438(Reward *dst, const Reward *src);

void PickWeightedReward_0207830c(Reward *out, int listIndex)
{
    RewardTier *row;
    int slot;
    RewardTier *tiers;
    int tier;
    int weight;
    u32 maxTier;
    int pick;
    RewardTableSet tables;

    tables = data_ov015_0207e868;
    maxTier = ReadGlobalPackedBits_02027348(0xf38, 4);
    if (maxTier >= 8 && GetPanelPageCount_020779dc() >= 100) {
        maxTier = 9;
    }
    if (maxTier >= 10) {
        maxTier = 9;
    }
    weight = 0;
    tiers = tables.lists[listIndex][data_ov015_020812e0->stage];
    tier = 0;
    pick = -1;
    for (; tier <= maxTier; tier++) {
        row = &tiers[tier];
        for (slot = 0; slot < 5; slot++) {
            weight += row->entries[slot].weight;
        }
    }
    weight = func_0202a9d0(weight);
    for (tier = 0; tier <= maxTier; tier++) {
        row = &tiers[tier];
        for (slot = 0; slot < 5; slot++) {
            weight -= row->entries[slot].weight;
            if (weight < 0) {
                pick = slot;
                break;
            }
        }
        if (slot < 5) {
            break;
        }
    }
    GrantRewardEntry_02078438(out, &row->entries[pick]);
}
