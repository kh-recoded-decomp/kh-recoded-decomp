#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern StageResourceItem *SpawnStageResourceItem(int category, u8 index, u8 animation, const VecFx32 *position,
                                                 BOOL persistent);

/*
 * Gives a primary entry (or one of kind 0x15) the effect item that shows it is under a status, once it has any
 * and is not out.
 */
void UpdateEntryStatusItem(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    BOOL hasStatus;
    int i;
    int category;
    int index;
    int animation;

    if (entry->memberIndex < work->primaryCount || entry->kind == 0x15) {
        hasStatus = FALSE;
        for (i = 0; i < STAGE_ENTRY_STATUS_COUNT; i++) {
            if (entry->statuses[i] != 0) {
                hasStatus = TRUE;
                break;
            }
        }
        if (hasStatus && entry->statusItem == NULL && entry->state != STAGE_ENTRY_OUT) {
            category = 0xff;
            index = 0x12;
            animation = 0;
            if (entry->kind == 0x15) {
                index = 0;
                category = 0x15;
                animation = 1;
            }
            entry->statusItem = SpawnStageResourceItem(category, index, animation, &entry->slot.node.position, TRUE);
        }
    }
}
