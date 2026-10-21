#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded the way the converter of the original tools did. */
#define FRAME_TO_FX32(x) ((x) > 0 ? (fx32)((f32)((x) << FX32_SHIFT) + 0.5f) : (fx32)((f32)((x) << FX32_SHIFT) - 0.5f))

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);

/*
 * Action handler for an action an entry uses on itself: plays its animation, shows its effect item on the
 * action's effect frame and gives itself status 2 for the action's turns, then ends the action.
 */
void EntryActionOnSelf(u8 entryIndex)
{
    StageEntry *entry = &gMovieContextState->stageWork->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame = GetEntryAnimationFrame(entry);
    VecFx32 position;

    switch (entry->stateStep) {
    case 0:
        entry->stateStep++;
    case 1:
        entry->mainTarget = entry->index;
        entry->targetCount = 1;
        entry->targets[0] = entry->mainTarget;
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        entry->stateStep++;
    case 2:
        if (frame < FRAME_TO_FX32(action->effectFrame)) {
            break;
        }
        GetEntryPosition(&position, entry);
        SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &position, FALSE);
        PlayStageSound(0xdd, 9, TRUE);
        entry->statuses[STAGE_ENTRY_STATUS_2] = action->statusTurns;
        entry->stateStep++;
    case 3:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        FinishEntryAction(entry);
        break;
    }
}
