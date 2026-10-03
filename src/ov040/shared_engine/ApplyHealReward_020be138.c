#include "nitro/types.h"

typedef struct HealthStats {
    u16 max;
    u16 current;
} HealthStats;

typedef struct RewardActor {
    u8 pad_000[0x1d4];
    HealthStats *health;
} RewardActor;

extern BOOL AddClampedHealth_020a75ec(RewardActor *actor, s16 delta);
extern int func_ov035_020baf88(void);
extern int func_ov035_020baf94(void);
extern void func_ov040_020bda6c(int entry, int amount);
extern void ApplyRewardByTier_020a7a40(RewardActor *actor, int kind, int tier);

void ApplyHealReward_020be138(RewardActor *actor, int kind, int tier)
{
    if (kind == 0) {
        int amount = 0;

        switch (tier) {
        case 0:
            amount = 1;
            break;
        case 1:
            amount = 10;
            break;
        case 2:
            amount = 100;
            break;
        }
        if (actor->health->current != 0 && amount > 0) {
            AddClampedHealth_020a75ec(actor, amount);
        }
        if (func_ov035_020baf88() > 0 && amount > 0) {
            func_ov040_020bda6c(1, amount);
        }
        if (func_ov035_020baf94() > 0 && amount > 0) {
            func_ov040_020bda6c(2, amount);
        }
        return;
    }
    ApplyRewardByTier_020a7a40(actor, kind, tier);
}

