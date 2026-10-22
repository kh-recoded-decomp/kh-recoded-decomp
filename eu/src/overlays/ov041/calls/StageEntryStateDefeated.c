#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole count as fx32, rounded half away from zero (converted once, after the rounding). */
#define INT_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

extern void ReleaseEntryStatusItem(u8 entryIndex);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void RequestFieldRefresh(void);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void ActorSlot_SetFlag8ByIndex(int actorIndex, BOOL enable);
extern int GetStageKindSoundArc(int kind);
extern void ActorSlot_SetFlag8(void *slot, BOOL enable);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern int func_0202a9e4(u16 range);
extern fx32 GetDifficultyScale(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern u8 CountActiveStageEntries(BOOL primary);
extern void StartStageOrbBurst(StageOrbBurst *burst, StageOrbPool *pool, StageEntry *collector,
                               const VecFx32 *position, fx32 amount);
extern void UpdateStageOrbBurst(StageOrbBurst *burst, StageOrbPool *pool);

static inline VecFx32 OverheadOf(StageEntry *entry)
{
    VecFx32 position;

    VEC_Add(&entry->slot.node.position, &entry->overheadOffset, &position);
    return position;
}

static inline StageWork *CurrentStageWork(void)
{
    return gMovieContextState->stageWork;
}

/*
 * Entry state 6 (defeated): clears its statuses (but status 3) and plays the hurt animation, with an enemy's
 * alternating cry. A player entry then goes down; an enemy vanishes with an effect and its kind's sound, and
 * unless it is not tallied throws out recovery orbs: a random amount in [orbsMin, orbsMax], scaled by the
 * difficulty, shared between the primary entries still standing (the remainder going to the lowest hp), each
 * share flying to its entry until the bursts are over.
 */
void StageEntryStateDefeated(u8 entryIndex)
{
    StageWork *work = CurrentStageWork();
    StageEntry *entry = &work->entries[entryIndex];
    int category = 0xc8;
    u8 index = 0;
    u8 animation = 0;
    VecFx32 position;
    StageOrbShares shares;
    StageOrbAmounts amounts;
    int amount;
    int remainder;
    int count;
    int i;
    int j;
    int swap;

    switch (entry->kind) {
    case 0:
    case 0x11:
    case 0x12:
        category = 0xff;
        index = 7;
        animation = 0;
        break;
    case 0x16:
    case 0x17:
        category = 0xff;
        index = 9;
        break;
    case 0xfd:
    case 0xfe:
    case 0xff:
        break;
    default:
        category = 0xff;
        index = 8;
        animation = 0;
        break;
    }
    if (entry->flags & STAGE_ENTRY_NOT_TALLIED) {
        category = 0xff;
        index = 8;
        animation = 0;
    }
    switch (entry->stateStep) {
    case 0:
        for (i = 0; i < STAGE_ENTRY_STATUS_COUNT; i++) {
            if (i != STAGE_ENTRY_STATUS_3) {
                entry->statuses[i] = 0;
            }
        }
        ReleaseEntryStatusItem(entry->index);
        entry->flags &= ~STAGE_ENTRY_GUARDING;
        entry->flags &= ~STAGE_ENTRY_HURT;
        entry->flags &= ~STAGE_ENTRY_DODGED;
        if (!(entry->flags & STAGE_ENTRY_NOT_TALLIED)) {
            SetSceneEntryAnimation(entry, entry->hurtAnimation, 1, 1);
            if ((entry->flags & STAGE_ENTRY_ENEMY) && entry->kind != 0x17) {
                if (entry->flags & STAGE_ENTRY_VOICE_TOGGLE) {
                    PlayStageSound(entry->voiceSeqArc, entry->altHurtVoices[1], TRUE);
                    entry->flags &= ~STAGE_ENTRY_VOICE_TOGGLE;
                } else {
                    PlayStageSound(entry->voiceSeqArc, entry->altHurtVoices[0], TRUE);
                    entry->flags |= STAGE_ENTRY_VOICE_TOGGLE;
                }
            }
        }
        entry->stateStep++;
    case 1:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        if (!(entry->flags & STAGE_ENTRY_ENEMY)) {
            SetSceneEntryAnimation(entry, entry->downAnimation, 1, 0);
            PlayStageSound(entry->voiceSeqArc, entry->downVoice, TRUE);
            if (entry->kind == 0xff) {
                RequestFieldRefresh();
            }
            entry->stateStep = 3;
            return;
        }
        switch (entry->kind) {
        case 0x17:
            SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
            PlayStageSound(0x44, 1, TRUE);
            break;
        case 0x15:
            if (entry->flags & STAGE_ENTRY_NOT_TALLIED) {
                VecFx32 shown;

                GetEntryOverheadPosition(&shown, entry);
                SpawnStageItem(entry, 0xff, 0xa, 0, &shown, FALSE);
                PlayStageSound(0, 0x24, FALSE);
                ActorSlot_SetFlag8ByIndex(entry->actorSlot, FALSE);
                break;
            }
        default: {
            VecFx32 shown;

            GetEntryOverheadPosition(&shown, entry);
            SpawnStageItem(entry, category, index, animation, &shown, FALSE);
            PlayStageSound(GetStageKindSoundArc(entry->kind), entry->downVoice, FALSE);
            ActorSlot_SetFlag8ByIndex(entry->actorSlot, FALSE);
            if (entry->kind == 0x12) {
                ActorSlot_SetFlag8(entry->attachment, FALSE);
            }
            break;
        }
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0xfd:
            break;
        }
        entry->stateStep++;
    case 2:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        if ((entry->flags & STAGE_ENTRY_ENEMY) && entry->orbsMin != 0 && !(entry->flags & STAGE_ENTRY_NOT_TALLIED)) {
            position = OverheadOf(entry);
            shares = gNoOrbShares;
            amounts = gNoOrbAmounts;
            amount = func_0202a9e4(entry->orbsMax - entry->orbsMin + 1) + entry->orbsMin;
            amount = FX_Mul(INT_TO_FX32(amount), GetDifficultyScale()) >> FX32_SHIFT;
            remainder = amount % CountActiveStageEntries(TRUE);
            count = work->primaryCount;
            for (i = 0; i < work->primaryCount; i++) {
                if (work->entries[i].state != STAGE_ENTRY_OUT) {
                    shares.entries[i].index = i;
                    shares.entries[i].hp = work->entries[i].hp;
                }
            }
            for (i = 0; i < work->primaryCount - 1; i++) {
                for (j = count - 1; j > i; j--) {
                    if (shares.entries[j - 1].hp < shares.entries[j].hp) {
                        swap = shares.entries[j].index;
                        shares.entries[j].index = shares.entries[j - 1].index;
                        shares.entries[j - 1].index = swap;
                        swap = shares.entries[j].hp;
                        shares.entries[j].hp = shares.entries[j - 1].hp;
                        shares.entries[j - 1].hp = swap;
                    }
                }
            }
            for (i = 0; i < work->primaryCount; i++) {
                j = shares.entries[i].index;
                if (j >= 0 && work->entries[j].state != STAGE_ENTRY_OUT) {
                    amounts.values[j] = INT_TO_FX32(amount / CountActiveStageEntries(TRUE));
                }
            }
            switch (remainder) {
            case 0:
                break;
            case 1:
                for (i = work->primaryCount - 1; i >= 0; i--) {
                    j = shares.entries[i].index;
                    if (j >= 0) {
                        amounts.values[j] += FX32_ONE;
                        break;
                    }
                }
                break;
            case 2:
                for (i = work->primaryCount - 1; i >= 0; i--) {
                    j = shares.entries[i].index;
                    if (j >= 0) {
                        amounts.values[j] += FX32_ONE;
                        if (--remainder == 0) {
                            break;
                        }
                    }
                }
                break;
            }
            for (i = 0; i < work->primaryCount; i++) {
                j = shares.entries[i].index;
                if (j >= 0 && work->entries[j].state != STAGE_ENTRY_OUT && amounts.values[j] >= FX32_ONE) {
                    StartStageOrbBurst(&entry->orbBursts[i], &work->orbPool, &work->entries[j], &position,
                                       amounts.values[j]);
                }
            }
        }
        entry->stateStep++;
    case 3:
        if ((entry->flags & STAGE_ENTRY_ENEMY) && entry->orbsMin != 0 && !(entry->flags & STAGE_ENTRY_NOT_TALLIED)) {
            for (i = 0; i < 3; i++) {
                if (entry->orbBursts[i].active) {
                    UpdateStageOrbBurst(&entry->orbBursts[i], &work->orbPool);
                }
            }
        }
        break;
    }
}
