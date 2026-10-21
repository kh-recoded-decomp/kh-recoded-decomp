#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SoundPair {
    u16 seqArcId;
    u16 soundId;
} SoundPair;

typedef struct OwnerSection {
    u32 unk_00;
    u32 count;
    u32 stride;
    u8 *data;
} OwnerSection;

typedef struct OwnerTable {
    OwnerSection sections[13];
} OwnerTable;

typedef struct OwnerBank {
    u8 pad_00[8];
    OwnerTable *table;
} OwnerBank;

typedef struct StageEntry {
    u8 pad_00[4];
    OwnerBank *bank;
} StageEntry;

typedef struct GroupInfo {
    u8 pad_00[0x11];
    u8 blockLow;
    u8 blockMid;
    u8 blockHigh;
} GroupInfo;

typedef struct GuardRate {
    u8 pad_00[6];
    u8 rate;
    u8 pad_07[0x19];
} GuardRate;

typedef struct EnemyGroup {
    s32 state;
    u16 pad4_0 : 4;
    u16 staggerLocked : 1;
    u16 hitHigh : 1;
    u16 pad4_6 : 1;
    u16 superArmor : 1;
    u16 hitSecondary : 1;
    u16 hitSpecial : 1;
    u16 hitNear : 1;
    u16 hitBreak : 1;
    u16 guarding : 1;
    u16 pad4_13 : 1;
    u16 guardFront : 1;
    u16 guardAll : 1;
    u16 noGuard : 1;
    u16 pad6_1 : 7;
    u16 bossGauge : 1;
    u16 invincible : 1;
    u16 defeatedNormally : 1;
    u16 pad6_11 : 4;
    u16 hitThisFrame : 1;
    u8 pad_08;
    u8 rank;
    u8 gaugeLevel;
    u8 pad_0b[3];
    u16 kind;
    u16 actorId;
    u16 guardId;
    s16 entryId;
    u8 pad_16[4];
    u16 dropId;
    u8 pad_1c[2];
    u16 stunTime;
    u8 pad_20[0x38];
    s8 resist[10];
    u8 stopOnHit;
    u8 dropAmount;
    u8 pad_64[8];
    u8 dropBonus;
    u8 pad_6d[3];
    s32 hp;
    s32 maxHp;
    u8 pad_78[0x24];
    s32 reward;
    GuardRate guardRates[8];
    u8 pad_1a0[0x10];
    s32 respawnDelay;
    u8 linkLow;
    u8 linkHigh;
} EnemyGroup;

typedef struct HitInfo {
    VecFx32 knockback;
    u8 pad_0c[0x10];
    s32 eventChance;
    s32 reward;
    u8 pad_24;
    u8 eventKind;
    u8 pad_26[2];
    u16 pad28_0 : 1;
    u16 secondary : 1;
    u16 special : 1;
    u16 pad28_3 : 3;
    u16 statGain : 1;
    u16 dropGain : 1;
    u16 piercing : 1;
    u16 instantKill : 1;
    u16 noWorldTarget : 1;
    u16 pad28_11 : 1;
    u16 breakLow : 1;
    u16 breakMid : 1;
    u16 breakHigh : 1;
    u16 pad28_15 : 1;
    u16 hitMask;
    u16 noReward;
    u16 stunTime;
    u8 pad_30[4];
    VecFx32 position;
    s32 totalDamage;
    u32 blocked : 1;
    u32 deflected : 1;
    u32 pad44_2 : 30;
} HitInfo;

typedef struct StageActor {
    u8 pad_000[0xac];
    fx32 facingX;
    u8 pad_0b0[4];
    fx32 facingZ;
    u8 pad_0b8[0x118];
    u8 words[0x9c];
    u32 stateFlags : 31;
    u32 pad26c_31 : 1;
    u8 pad_270[0x1c];
    u16 pad28c_0 : 3;
    u16 guardIndex : 4;
    u16 guardLevel : 4;
    u16 pad28c_11 : 5;
    u8 pad_28e[2];
    fx32 groundY;
    fx32 stunVelocity;
    u8 pad_298[0x28];
    VecFx32 position;
    u8 pad_2cc[0x9c];
    VecFx32 knockback;
    u8 pad_374[0x24];
    s32 knockbackLimit;
    u8 pad_39c[0x10];
    u16 airTime;
} StageActor;

typedef struct TargetWorld {
    u8 pad_00000[0x18f38];
    u8 searched;
    u8 locked;
    u16 targetRow;
    fx32 targetDistance;
} TargetWorld;

typedef struct SmallRecord {
    u8 pad_00[4];
    s8 statIndex;
} SmallRecord;

typedef struct SpawnParams {
    u16 walkerKind;
    u16 ownerSlot;
    u16 spawnArg;
    u16 attachActorId;
    u16 attach : 1;
    u16 align : 1;
    u16 attachDefault : 1;
    u16 unused : 13;
    u16 pad_0a;
    s32 nodeName;
} SpawnParams;

typedef struct AttachPoint {
    u32 key;
    s32 nameIndex;
    u8 pad_08[0xc];
    VecFx32 scale;
} AttachPoint;

typedef struct StageController {
    u8 pad_00[8];
    u16 pad8_0 : 2;
    u16 visible : 1;
    u16 active : 1;
    u16 pad8_4 : 12;
} StageController;

extern VecFx32 data_02053438;

extern StageActor *GetStageActor_0209c040(int id);
extern StageEntry *GetStageEntry_0209c074(int id);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern s32 nextRandom12_0202aa58(void);
extern BOOL Session_Exists_02063a24(void);
extern int func_ov001_02063a38(void);
extern void AddSessionCounter_02063a80(int index, int amount);
extern BOOL func_ov001_0209d064(u32 id);
extern void func_ov001_02091ac0(StageActor *actor, u32 firstId, u32 secondId, int flags);
extern u32 PlayStageSoundAt_0209d080(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);
extern void CopySourceWords_020b4b7c(void *cache);
extern void func_ov001_020925bc(EnemyGroup *group, int state);
extern void func_ov001_020925c8(EnemyGroup *group, int level);
extern TargetWorld *func_ov001_0209c3c0(void);
extern u16 GetStageRowIndex_0209c228(EnemyGroup *group);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_ov001_0209c544(u16 id, u16 value);
extern void PlayAlternatingStageSound_0209279c(EnemyGroup *group, StageActor *actor, StageEntry *owner, BOOL secondary);
extern void ForwardToGroupActorComponent_0209260c(EnemyGroup *group, int arg);
extern s32 func_ov001_02097a84(EnemyGroup *group, HitInfo *hit, int index);
extern void ScheduleSpawnerNextTime_02096928(EnemyGroup *group, int baseTime);
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern void ResetGroupLeaderAndSetState_02097a1c(EnemyGroup *group);
extern void func_ov001_02093188(EnemyGroup *group);
extern void SetStageEventKind_02092afc(EnemyGroup *group, u32 kind);
extern SmallRecord *GetSmallTableEntry_0209c340(int index);
extern void ApplyPartyStatGain_02066684(int index, void *target, int amount, BOOL scaled);
extern void func_ov001_02068a74(int index, VecFx32 *position, u32 amount);
extern void ClearActorMotionState_02091194(StageActor *actor);
extern void ClearWalkerStepState_02091964(StageActor *actor);
extern void func_01ff88c4(void *dst, int value, u32 size);
extern void FindStageAttachPoint_02097890(EnemyGroup *group, u32 key, AttachPoint *out);
extern int SpawnStageObjectActor_02096ae0(EnemyGroup *group, SpawnParams *params, VecFx32 *position);
extern StageController *GetStageController_0209c120(int id);
extern void Obj_SetField14_0209839c(StageController *controller, fx32 value);

static inline void SetVec(VecFx32 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline int GetSessionMode(void)
{
    if (Session_Exists_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

static inline u32 GetSoundCount(StageEntry *owner)
{
    if (owner == NULL) {
        return 0;
    }
    if (owner->bank == NULL) {
        return 0;
    }
    return owner->bank->table->sections[12].count;
}

static inline SoundPair *GetSoundPair(StageEntry *owner, int index)
{
    u32 count;
    OwnerTable *table;
    u8 *entries;

    if (owner == NULL) {
        return NULL;
    }
    if (owner->bank == NULL) {
        return NULL;
    }
    count = GetSoundCount(owner);
    table = owner->bank->table;
    entries = table->sections[12].data;
    if (count == 0) {
        return NULL;
    }
    if (count <= (u16)index) {
        return NULL;
    }
    return (SoundPair *)(entries + (u16)index * table->sections[12].stride);
}

static inline u32 GetSectionCount(StageEntry *owner, int index)
{
    if (owner == NULL) {
        return 0;
    }
    if (owner->bank == NULL) {
        return 0;
    }
    return owner->bank->table->sections[index].count;
}

static inline void *GetSectionElement(StageEntry *owner, int index, u32 element)
{
    OwnerTable *table;
    u32 count;
    u8 *data;

    if (owner == NULL) {
        return NULL;
    }
    if (owner->bank == NULL) {
        return NULL;
    }
    count = GetSectionCount(owner, index);
    table = owner->bank->table;
    data = table->sections[index].data;
    if (count == 0) {
        return NULL;
    }
    if (element >= count) {
        return NULL;
    }
    return data + element * table->sections[index].stride;
}

static inline void DefeatGroup(EnemyGroup *group, HitInfo *hit, StageActor *actor, StageEntry *owner, BOOL wasFull)
{
    SoundPair *pair;

    if (hit->noReward == 0) {
        if (wasFull) {
            AddSessionCounter_02063a80(0x14, 1);
        }
        if (group->rank == 3) {
            AddSessionCounter_02063a80(0x1c, 1);
        } else {
            AddSessionCounter_02063a80(0x13, 1);
        }
        if (group->kind == 0x3e) {
            AddSessionCounter_02063a80(0x19, 1);
        }
        if (group->kind == 0x3f) {
            AddSessionCounter_02063a80(0x1a, 1);
        }
    }
    if (func_ov001_0209d064(group->kind)) {
        AddSessionCounter_02063a80(0x1b, 1);
    }
    func_ov001_02091ac0(actor, 0xffff, 0xffff, 0);
    pair = GetSoundPair(owner, 5);
    if (pair != NULL && pair->soundId != 0) {
        PlayStageSoundAt_0209d080(pair->seqArcId, pair->soundId, &actor->position, 0);
    }
    group->defeatedNormally = hit->noReward == 0;
    group->hp = 0;
    CopySourceWords_020b4b7c(actor->words);
    func_ov001_020925bc(group, 7);
    hit->reward = group->reward;
}

BOOL ApplyHitToEnemyGroup_020958f4(EnemyGroup *group, HitInfo *hit)
{
    StageActor *actor = GetStageActor_0209c040((s16)group->actorId);
    StageEntry *owner = GetStageEntry_0209c074(group->entryId);
    s32 total;
    BOOL near;
    u32 bits;
    BOOL wasFull;
    BOOL instant;
    u32 chance;
    u32 mask;

    random_next_scaled_0202aa04(100);
    if (GetSessionMode() != 6) {
        if (group->state == 2 && group->respawnDelay > 0) {
            return FALSE;
        }
        if (group->bossGauge && group->rank == 4 && group->state == 0xb) {
            return FALSE;
        }
    }
    if (group->state == 6) {
        return FALSE;
    }
    if (group->invincible) {
        return FALSE;
    }
    if (hit->special && !group->superArmor) {
        return FALSE;
    }
    group->hitThisFrame = 0;
    hit->blocked = 0;
    hit->deflected = 0;
    group->hitSecondary = 0;
    group->hitHigh = 0;
    group->hitNear = 0;
    group->hitBreak = 0;
    wasFull = FALSE;
    group->stunTime = 0;
    if (group->hp <= 0) {
        return FALSE;
    }
    if (group->hp == group->maxHp) {
        wasFull = TRUE;
    }
    instant = FALSE;
    if (group->rank != 4 && hit->instantKill) {
        instant = TRUE;
    }
    if (instant) {
        DefeatGroup(group, hit, actor, owner, wasFull);
        return TRUE;
    }
    if (!hit->breakLow && !hit->special && hit->noReward == 0 && !hit->noWorldTarget && group->rank == 3) {
        TargetWorld *world = func_ov001_0209c3c0();
        StageActor *leader = GetStageActor_0209c040((s16)group->actorId);
        world->searched = 1;
        if (world->locked == 0 && world != NULL) {
            u16 row = GetStageRowIndex_0209c228(group);
            if ((leader->stateFlags & 0x200000) || leader->airTime != 0 || leader->groundY == leader->position.y) {
                VecFx32 delta;
                fx32 distance;
                VEC_Subtract_01ff9e3c(&leader->position, &hit->position, &delta);
                distance = VEC_Mag_01ff9f28(&delta);
                if (world->targetRow == 0 || distance < world->targetDistance) {
                    world->targetRow = row;
                    world->targetDistance = distance;
                }
            }
        }
        return FALSE;
    }
    if (group->guarding) {
        hit->deflected = 1;
        return FALSE;
    }
    if (GetSessionMode() == 7) {
        near = TRUE;
    } else {
        VecFx32 facing;
        VecFx32 direction;
        VecFx32 diff;
        VEC_Subtract_01ff9e3c(&hit->position, &actor->position, &diff);
        near = FALSE;
        diff.y = 0;
        if (VEC_Mag_01ff9f28(&diff) < 0x80) {
            near = TRUE;
        } else {
            VEC_Normalize_01ffaff4(&diff, &direction);
            SetVec(&facing, actor->facingX, 0, actor->facingZ);
            VEC_Normalize_01ffaff4(&facing, &facing);
            if (VEC_DotProduct_01ff9e6c(&direction, &facing) >= 0x4cd) {
                near = TRUE;
            }
        }
    }
    if (GetSessionMode() == 6) {
        if (hit->special) {
            return FALSE;
        }
        if (group->state == 6) {
            return FALSE;
        }
        if (group->state == 7) {
            return FALSE;
        }
        if (func_ov001_0209c544(group->guardId, near ? 1 : 2)) {
            PlayAlternatingStageSound_0209279c(group, actor, owner, hit->secondary);
            return TRUE;
        }
    }
    if (group->noGuard) {
        chance = 0;
    } else {
        if (hit->piercing) {
            goto damage;
        }
        if (!group->guardFront && !group->guardAll) {
            if (group->state == 4 || !near || actor->guardLevel == 0 || !(actor->stateFlags & 0x200) || hit->special) {
                goto damage;
            }
            chance = random_next_scaled_0202aa04(100);
        } else {
            GroupInfo *info;
            if ((group->guardFront && !near) || hit->special) {
                goto damage;
            }
            info = GetSectionElement(owner, 0, 0);
            if (info != NULL && ((info->blockLow == 0 && hit->breakLow) || (info->blockMid == 0 && hit->breakMid) || (info->blockHigh == 0 && hit->breakHigh))) {
                goto damage;
            }
            chance = 0;
        }
    }
    if (chance <= group->guardRates[actor->guardIndex - 1].rate) {
        AttachPoint attach;
        SpawnParams params;
        StageController *controller;
        SoundPair *pair;

        ForwardToGroupActorComponent_0209260c(group, 5);
        func_01ff88c4(&params, 0, sizeof(params));
        FindStageAttachPoint_02097890(group, 2, &attach);
        params.ownerSlot = 0xb;
        params.attach = 1;
        params.attachDefault = 0;
        params.attachActorId = group->actorId;
        params.nodeName = attach.nameIndex;
        params.align = 0;
        controller = GetStageController_0209c120(SpawnStageObjectActor_02096ae0(group, &params, NULL));
        if (controller != NULL) {
            controller->visible = 1;
            controller->active = 1;
            Obj_SetField14_0209839c(controller, attach.scale.x);
        }
        pair = GetSoundPair(owner, 4);
        if (pair != NULL) {
            PlayStageSoundAt_0209d080(pair->seqArcId, pair->soundId, &actor->position, 0);
        }
        hit->blocked = 1;
        return TRUE;
    }
damage:
    if (!hit->special) {
        u16 i;
        total = 0;
        mask = hit->hitMask;
        if (mask == 0) {
            mask = 1;
        }
        ForwardToGroupActorComponent_0209260c(group, 1);
        i = 0;
        bits = (u16)mask;
        for (; i < 8; i++) {
            if (bits & (1 << i)) {
                s32 damage = func_ov001_02097a84(group, hit, i);
                group->hp -= damage;
                total += damage;
                if (group->stopOnHit == 1) {
                    break;
                }
            }
        }
        hit->totalDamage = total;
    }
    group->hitNear = near;
    group->hitBreak = hit->breakLow;
    group->hitSecondary = hit->secondary;
    group->hitSpecial = hit->special;
    group->hitHigh = hit->breakHigh;
    actor->stunVelocity = 0;
    ForwardToGroupActorComponent_0209260c(group, 2);
    if (group->hp <= 0) {
        func_ov001_02091ac0(actor, 0xffff, 0xffff, 0);
        group->linkLow = 0;
        group->linkHigh = 0;
        DefeatGroup(group, hit, actor, owner, wasFull);
    } else {
        BOOL stagger;
        if (hit->special) {
            ScheduleSpawnerNextTime_02096928(group, 0);
        } else {
            PlayAlternatingStageSound_0209279c(group, actor, owner, hit->secondary);
        }
        if (group->bossGauge && group->rank == 4) {
            fx32 ratio = FX_Div_01ff9c84(group->hp, group->maxHp);
            int level = 4;
            if (ratio < 0x19a) {
                level = 3;
            } else if (ratio < 0x666) {
                level = 1;
            } else if (ratio < 0xb33) {
                level = 2;
            }
            func_ov001_020925c8(group, level);
            if (group->gaugeLevel != level) {
                ResetGroupLeaderAndSetState_02097a1c(group);
                func_ov001_02093188(group);
                goto done;
            }
        }
        stagger = FALSE;
        if (group->rank != 4) {
            if (hit->eventKind != 0 && hit->eventChance != 0 && nextRandom12_0202aa58() * 100 < hit->eventChance &&
                random_next_scaled_0202aa04(10000) >= group->resist[hit->eventKind - 1] * 100) {
                stagger = TRUE;
            }
            if (stagger) {
                SetStageEventKind_02092afc(group, hit->eventKind);
            }
        }
        stagger = FALSE;
        if (group->state != 10) {
            stagger = TRUE;
            if (group->staggerLocked) {
                stagger = FALSE;
            }
            if (group->gaugeLevel == 1) {
                stagger = FALSE;
            }
            if (group->gaugeLevel == 3) {
                stagger = FALSE;
            }
        }
        if (!stagger && group->rank != 4) {
            group->hitThisFrame = 1;
        }
        if (stagger) {
            SmallRecord *record;
            group->linkLow = 0;
            group->linkHigh = 0;
            func_ov001_02091ac0(actor, 0xffff, 0xffff, 0);
            if (group->dropId != 0xffff && (record = GetSmallTableEntry_0209c340(group->dropId)) != NULL) {
                if (hit->statGain) {
                    ApplyPartyStatGain_02066684(record->statIndex, &actor->position, group->dropAmount, TRUE);
                }
                if (hit->dropGain) {
                    func_ov001_02068a74(group->dropId, &actor->position, group->dropBonus);
                }
            }
            actor->knockback = hit->knockback;
            if (actor->knockbackLimit == 0x7fffffff) {
                actor->knockback = data_02053438;
            }
            ClearActorMotionState_02091194(actor);
            CopySourceWords_020b4b7c(actor->words);
            ClearWalkerStepState_02091964(actor);
            group->stunTime = hit->stunTime;
            actor->stunVelocity = -0x19a;
            func_ov001_020925bc(group, 5);
        }
    }
done:
    return TRUE;
}
