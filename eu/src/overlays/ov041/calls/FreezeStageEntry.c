#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void Flags16_SetBit1(u16 *flags);

/*
 * Freezes an entry for a number of frames: pauses its models (for the player kinds also the primary model and
 * their shadow actor) and holds its effect items. Not in the fast panel mode.
 */
void FreezeStageEntry(StageEntry *entry, int frames)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;

    if (work->flags & STAGE_WORK_FAST_PANELS) {
        return;
    }
    Flags16_SetBit1(&entry->slot.node.flags);
    entry->delay = frames;
    entry->flags |= STAGE_ENTRY_FROZEN;
    if (entry->kind == 0xff) {
        Flags16_SetBit1(&work->primaryActor.node.flags);
        Flags16_SetBit1(&work->shadowActors[0]->node.flags);
        work->shadowActors[0]->stateFlags |= 0x20;
    } else if (entry->kind == 0xfd) {
        Flags16_SetBit1(&work->shadowActors[1]->node.flags);
        work->shadowActors[1]->stateFlags |= 0x20;
    } else if (entry->kind == 0x16) {
        Flags16_SetBit1(&entry->attachment->node.flags);
    }
    for (i = 0; i < 5; i++) {
        if (entry->effects[i] != NULL) {
            entry->effects[i]->flags |= STAGE_ITEM_HELD;
        }
    }
}
