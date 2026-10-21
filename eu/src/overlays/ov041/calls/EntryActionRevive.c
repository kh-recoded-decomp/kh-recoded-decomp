#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

typedef float f32;

/* A whole frame count as fx32, rounded the way the converter of the original tools did. */
#define FRAME_TO_FX32(x) ((x) > 0 ? (fx32)((f32)((x) << FX32_SHIFT) + 0.5f) : (fx32)((f32)((x) << FX32_SHIFT) - 0.5f))

#define STAGE_ENTRY_REVIVING 11

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void PlayEntryActionSound(StageEntry *entry, fx32 frame);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void SetEntryState(StageEntry *entry, int state);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);

/*
 * Action handler for the revive: plays the action, and on its cast frame starts reviving every one of the first
 * three secondary entries that is out; back on its idle animation it ends the action. A sound marks the first
 * frame of the action's animation.
 */
void EntryActionRevive(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame = GetEntryAnimationFrame(entry);
    int i;

    PlayEntryActionSound(entry, frame);
    switch (entry->stateStep) {
    case 0:
        entry->stateStep++;
    case 1:
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        PlayEntryActionSound(entry, frame);
        entry->stateStep++;
    case 2:
        if (frame < FRAME_TO_FX32(action->castFrame)) {
            break;
        }
        for (i = 0; i < 3; i++) {
            if (work->entries[i + work->primaryCount].state == STAGE_ENTRY_OUT) {
                SetEntryState(&work->entries[i + work->primaryCount], STAGE_ENTRY_REVIVING);
            }
        }
        entry->stateStep++;
    case 3:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
        entry->stateStep++;
    case 4:
        for (i = 0; i < 3; i++) {
            if (work->entries[work->primaryCount + i].state != STAGE_ENTRY_WAITING) {
                break;
            }
        }
        FinishEntryAction(entry);
        break;
    }
    if (MatchesEitherSlotId(entry, action->animation) && frame >= 0 && frame < FX32_ONE) {
        PlayStageSound(0x44, 4, TRUE);
    }
}
