#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern u32 func_ov041_020c4d58(StageEntry *entry, StageEntry *target, StageEntryHit *hit);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern void FreezeStageEntry(StageEntry *entry, int frames);

static inline StageResourceItem *SpawnEffectAbove(StageEntry *entry, const StageItemSpec *effect, StageEntry *target)
{
    VecFx32 position;

    GetEntryOverheadPosition(&position, target);
    return SpawnStageItem(entry, effect->category, effect->index, effect->animation, &position, FALSE);
}

static inline VecFx32 OverheadOf(StageEntry *entry)
{
    VecFx32 position;

    GetEntryOverheadPosition(&position, entry);
    return position;
}

static inline VecFx32 GridOf(u8 row, u8 column)
{
    VecFx32 position;

    GetStageGridPosition(&position, row, column);
    return position;
}

/*
 * ApplyActionHit with the hit sound given: resolves an entry's hit on one target and shows its effects, playing
 * seqArcNo/soundIndex where ApplyActionHit plays the action's hit sound.
 */
void ApplyActionHitWithSound(StageEntry *entry, u8 targetIndex, BOOL pressCheck, int seqArcNo, int soundIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntryHit *hit = &entry->hit;
    StageEntryAction *action = GetEntryAction(entry);
    VecFx32 grid;
    VecFx32 missPosition;
    u32 result;
    BOOL landed;

    result = func_ov041_020c4d58(entry, &work->entries[targetIndex], hit);
    landed = result & 1;
    if (landed) {
        if (!(entry->flags & STAGE_ENTRY_ENEMY) && (result & 2)) {
            SpawnEffectAbove(entry, &hit->altEffect, &work->entries[targetIndex]);
            PlayStageSound(seqArcNo, soundIndex, TRUE);
        } else {
            SpawnEffectAbove(entry, &hit->effect, &work->entries[targetIndex]);
            if (!(result & 8)) {
                PlayStageSound(seqArcNo, soundIndex, TRUE);
            }
        }
    } else {
        entry->flags |= STAGE_ENTRY_MISSED;
        if (action->kind == 1 && action->healEffectIndex == 3) {
            PlayStageSound(seqArcNo, soundIndex, TRUE);
        }
        switch (action->kind) {
        case 2:
        case 10:
        case 11:
            grid = GridOf(work->entries[targetIndex].row, work->entries[targetIndex].column);
            missPosition = OverheadOf(&work->entries[targetIndex]);
            missPosition.x = grid.x;
            SpawnStageItem(entry, hit->effect.category, hit->effect.index, hit->effect.animation, &missPosition,
                           FALSE);
            break;
        }
    }
    if (result & 0x10) {
        StageResourceItem *item = SpawnEffectAbove(entry, &hit->effect, &work->entries[targetIndex]);

        if (item != NULL) {
            item->model.scale.x = 2 * FX32_ONE;
            item->model.scale.y = 2 * FX32_ONE;
            item->model.scale.z = 2 * FX32_ONE;
        }
        PlayStageSound(seqArcNo, soundIndex, TRUE);
    }
    if (pressCheck) {
        if ((entry->flags & STAGE_ENTRY_PRESS_PANEL) || (work->entries[targetIndex].flags & STAGE_ENTRY_PRESS_PANEL)) {
            if (landed) {
                FreezeStageEntry(entry, 9 * FX32_ONE);
                FreezeStageEntry(&work->entries[entry->mainTarget], 9 * FX32_ONE);
            }
        }
    }
}
