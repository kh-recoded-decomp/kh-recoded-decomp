#include "nitro/types.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 level;
    u8 rank;
} RandomReward;

extern u32 func_0202a9e4(u32 range);

void RollRandomRewardStats(RandomReward *reward)
{
    if (func_0202a9e4(0x80) == 1) {
        int i;
        int tier;
        tier = 0;
        i = 0;
        do {
            if (func_0202a9e4(6) != 0) {
                break;
            }
            tier++;
            i++;
        } while (i < 9);
        reward->level = func_0202a9e4((u16)(tier * 10 + 9)) + 1;
        if (reward->level > 99) {
            reward->level = 99;
        }
    }
    if (func_0202a9e4(0x80) == 2) {
        reward->rank = 1;
    }
    if (func_0202a9e4(0x80) == 3) {
        if (reward->rank == 1) {
            reward->rank = 3;
            return;
        }
        reward->rank = 2;
    }
}
