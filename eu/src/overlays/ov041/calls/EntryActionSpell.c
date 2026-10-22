#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define EFFECT_RAISE 0x19a /* how far above the target the spell's effect item shows */

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern BOOL IsStageEntryFrozen(StageEntry *entry);
extern void FillActionTargets(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern int func_0202a9e4(u16 range);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern StageResourceItem *SpawnStageResourceItem(int category, u8 index, u8 animation, const VecFx32 *position,
                                                 BOOL persistent);
extern int Anim_GetFrame(void *anim, int track);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern void FinishEntryAction(StageEntry *entry);
extern u32 IsEntryFlag2Set(StageEntry *entry);

static inline VecFx32 OverheadOf(StageEntry *entry)
{
    VecFx32 position;

    GetEntryOverheadPosition(&position, entry);
    return position;
}

/*
 * Action handler for a spell: plays the casting animation and one of two sounds, then on the cast frame shows
 * the spell's effect item over the target (or its column, the middle of the field, or every primary entry for
 * target kind 8); once the item's animation has run its length the hit is resolved, and the action ends after
 * the item is gone. Effect 0xe7 also plays a sound three frames before the hit.
 */
void EntryActionSpell(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame = GetEntryAnimationFrame(entry);
    VecFx32 position;
    int i;

    if (!IsStageEntryFrozen(entry)) {
        data_ov041_020cff48.castTimer += FX32_ONE;
    }
    switch (entry->stateStep) {
    case 0:
        data_ov041_020cff48.castTimer = 0;
        entry->stateStep++;
    case 1:
        FillActionTargets(entry);
        SetSceneEntryAnimation(entry, action->animation, 0, 1);
        frame = GetEntryAnimationFrame(entry);
        if (func_0202a9e4(2000) / 1000 == 0) {
            PlayStageSound(0x30, 0, TRUE);
        } else {
            PlayStageSound(0x30, 1, TRUE);
        }
        entry->stateStep++;
    case 2:
        if (data_ov041_020cff48.castTimer < FRAME_TO_FX32(action->castFrame)) {
            break;
        }
        switch (action->targetKind) {
        case 0:
            GetEntryOverheadPosition(&position, &work->entries[entry->mainTarget]);
            break;
        case 1:
            GetStageGridPosition(&position, 1, work->entries[entry->mainTarget].column);
            break;
        case 4:
            GetStageGridPosition(&position, 1, 1);
            break;
        case 7:
            GetEntryOverheadPosition(&position, &work->entries[entry->mainTarget]);
            break;
        case 8:
            GetEntryOverheadPosition(&position, &work->entries[entry->mainTarget]);
            for (i = 0; i < work->primaryCount; i++) {
                if (i > 0) {
                    VecFx32 shown = OverheadOf(&work->entries[i]);

                    shown.y += EFFECT_RAISE;
                    SpawnStageResourceItem(action->effectCategory, action->effectIndex, action->effectAnimation, &shown,
                                           FALSE);
                }
            }
            break;
        }
        position.y += EFFECT_RAISE;
        entry->effects[0] =
            SpawnStageResourceItem(action->effectCategory, action->effectIndex, action->effectAnimation, &position, FALSE);
        PlayStageSound(0x1a0, action->soundIndex, TRUE);
        entry->stateStep++;
    case 3:
        if (action->effect == 0xe7 && entry->effects[0] != NULL) {
            int effectFrame = Anim_GetFrame(&entry->effects[0]->model, 0);

            if (FRAME_TO_FX32(action->effectLength) - 3 * FX32_ONE <= effectFrame &&
                effectFrame < FRAME_TO_FX32(action->effectLength) - 2 * FX32_ONE) {
                PlayStageSound(0x1a0, 0x1b, TRUE);
            }
        }
        if (entry->effects[0] != NULL &&
            Anim_GetFrame(&entry->effects[0]->model, 0) < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        ComputeEntryHit(entry, &entry->hit);
        ApplyActionToTargets(entry);
        entry->stateStep++;
    case 4:
        if (entry->effects[0] != NULL && (entry->effects[0]->flags & 4)) {
            break;
        }
        if (!MatchesEitherSlotId(entry, action->animation)) {
            FinishEntryAction(entry);
        }
        break;
    }
    if (MatchesEitherSlotId(entry, action->animation) && !IsEntryFlag2Set(entry)) {
        SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
    }
}
