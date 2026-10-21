#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void SetEntryState(StageEntry *entry, int state);

/*
 * Entry state handler for an entry appearing: waits five frames per place after the primary entries, plays the
 * appear effect, then animation 3, and once that is over starts at full hp on its idle animation.
 */
void StageEntryStateAppear(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    VecFx32 position;

    switch (entry->stateStep) {
    case 0:
        entry->waitFrames = 0;
        entry->stateStep++;
    case 1:
        if (entry->waitFrames < (entry->index - work->primaryCount) * 5) {
            entry->waitFrames++;
            return;
        }
        entry->stateStep++;
    case 2:
        GetPositionAboveGround(&position, entry);
        entry->effects[0] = SpawnStageItem(entry, 0xff, 1, 0, &position, FALSE);
        entry->stateStep++;
    case 3:
        if (entry->effects[0]->flags & STAGE_ITEM_IN_USE) {
            break;
        }
        entry->effects[0] = NULL;
        ActorSlot_SetFlag8ByIndex(entry->actorSlot, TRUE);
        SetSceneEntryAnimation(entry, 3, 0, 0);
        entry->stateStep++;
    case 4:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        entry->hp = entry->maxHp;
        entry->shownHp = entry->maxHp;
        SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
        SetEntryState(entry, STAGE_ENTRY_WAITING);
        break;
    }
}
