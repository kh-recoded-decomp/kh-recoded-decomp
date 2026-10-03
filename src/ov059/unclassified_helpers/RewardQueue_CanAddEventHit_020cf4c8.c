#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RewardEntry {
    u16 eventId;
    u16 subId;
    int type;
} RewardEntry;

typedef struct RewardQueue {
    u8 pad_000[0x60];
    RewardEntry entries[16];
    fx32 timers[8];
    fx32 fades[8];
    u8 count;
    u8 capacity;
} RewardQueue;

typedef struct EventTargetInfo {
    u16 id;
    u16 flags;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 hitPoints;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct AttackDesc {
    fx32 power;
    u8 pad_04[0xc];
    u8 attackType;
    u8 element;
    u8 pad_12[0x28 - 0x12];
} AttackDesc;

typedef struct HitInfo {
    VecFx32 direction;
    fx32 damage;
    u8 pad_10[0x2a - 0x10];
    u16 targetSubId;
    u8 pad_2c[2];
    u16 unk_2e;
    u16 attackerLevel;
    u8 pad_32[2];
    VecFx32 origin;
    u8 pad_40[0x48 - 0x40];
} HitInfo;

typedef struct PlayerStats {
    u8 pad_00;
    u8 level;
} PlayerStats;

typedef struct PlayerEntry {
    u8 pad_000[0x1d4];
    PlayerStats *stats;
} PlayerEntry;

extern const VecFx32 data_02053438;
extern void GetStageEventTargetInfo_02087960(u16 id, EventTargetInfo *info);
extern void ZeroBytes0x28_020ac0f8(void *obj);
extern void func_01ff8830(void *dest, u32 value, u32 size);
extern PlayerEntry *GetBoundedEntryField_0206db5c(int player);
extern VecFx32 *func_ov001_0206dc4c(int player);
extern fx32 ComputeAttackDamage_020ac6cc(int player, AttackDesc *attack);
extern s32 func_ov001_020880b4(u32 eventId, HitInfo *hit, u32 subId);

BOOL RewardQueue_CanAddEventHit_020cf4c8(RewardQueue *queue, u16 eventId, u16 subId) {
    HitInfo hit;
    EventTargetInfo info;
    AttackDesc attack;
    u32 count = queue->count;
    u8 i = 0;
    u8 matches = 0;

    for (; i < count; i++) {
        if (queue->entries[i].type == 2 && eventId == queue->entries[i].eventId
            && subId == queue->entries[i].subId) {
            if (queue->fades[i] < 0x5000) {
                return FALSE;
            }
            matches++;
        }
    }
    if (matches == 0) {
        return TRUE;
    }
    GetStageEventTargetInfo_02087960(eventId, &info);
    ZeroBytes0x28_020ac0f8(&attack);
    attack.power = 0x1800;
    attack.attackType = 0;
    func_01ff8830(&hit, 0, sizeof(HitInfo));
    hit.unk_2e = 0;
    hit.attackerLevel = GetBoundedEntryField_0206db5c(0)->stats->level;
    hit.origin = *func_ov001_0206dc4c(0);
    hit.direction = data_02053438;
    hit.targetSubId = subId;
    hit.damage = ComputeAttackDamage_020ac6cc(0, &attack);
    {
        s32 damage = func_ov001_020880b4(eventId, &hit, subId);
        return damage * matches < info.hitPoints << 12;
    }
}
