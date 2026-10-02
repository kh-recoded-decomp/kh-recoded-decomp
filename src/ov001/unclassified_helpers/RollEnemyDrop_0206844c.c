#include "nitro/types.h"

typedef struct {
    u16 id;
    u8 bonus;
    u8 extra;
} RewardItem;

typedef struct {
    s16 id;
    u8 bonus;
    u8 extra;
    u16 chance;
} DropEntry;

typedef struct {
    u8 pad_00[0xc];
    u16 level;
} SelectionRecord;

extern s16 data_ov001_0209da52[];
extern DropEntry *GetRecordSlot5Entry_0205208c(int recordId);
extern u32 GetSessionStateFlags2Bit_020649b8(void);
extern SelectionRecord *func_0204f768(u32 index);
extern int func_020275c8(void);
extern int ComputeScaledPercentPlusOne_02051134(void);
extern u32 func_0202a9d0(u32 range);
extern void RollLevelBonus_0206838c(int level, RewardItem *reward);
extern void RollRandomRewardStats_020683e0(RewardItem *reward);
extern u32 func_ov001_020664f0(int kind, u32 reward, u32 owner, int flags);
extern void SetGlobalPackedBit_02027320(int bit);

static inline BOOL IsEquipmentId(int id)
{
    return id >= 0 && id <= 0x7f;
}

void RollEnemyDrop_0206844c(int level, int recordId, u32 owner, BOOL reduced)
{
    DropEntry *entries = GetRecordSlot5Entry_0205208c(recordId);
    u32 slot = GetSessionStateFlags2Bit_020649b8();
    DropEntry *entry = &entries[slot];
    int chance;
    RewardItem reward;
    SelectionRecord *record;

    if (entry->id < 0) {
        return;
    }
    chance = entry->chance;
    record = func_0204f768(0);
    chance = chance * func_020275c8();
    chance = chance * (((s32)(record->level << 7) >> 2) + 0x80);
    chance = ((chance >> 7) * ComputeScaledPercentPlusOne_02051134()) >> 12;
    if (chance > 10000) {
        chance = 10000;
    }
    if (reduced) {
        chance /= 8;
    }
    if ((int)func_0202a9d0(10000) >= chance) {
        return;
    }
    reward.id = entry->id;
    reward.bonus = entries[slot].bonus;
    reward.extra = entries[slot].extra;
    if (reward.id == 0xcf) {
        reward.id = data_ov001_0209da52[func_0202a9d0(13)];
    }
    if (reward.bonus == 0xff) {
        RollLevelBonus_0206838c(level, &reward);
    }
    if (IsEquipmentId(reward.id)) {
        RollRandomRewardStats_020683e0(&reward);
    }
    func_ov001_020664f0(6, *(u32 *)&reward, owner, 0);
    SetGlobalPackedBit_02027320(slot + (recordId * 4 + 0x5c0));
}





