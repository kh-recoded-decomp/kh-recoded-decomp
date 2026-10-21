#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/*
 * Moves an entry to another state, remembering the one it leaves. Going between waiting and active keeps its
 * pending mark; any other change clears it.
 */
void SetEntryState(StageEntry *entry, int state)
{
    if (entry->state == state) {
        return;
    }
    entry->previousState = entry->state;
    if (entry->state == STAGE_ENTRY_WAITING || entry->state == STAGE_ENTRY_ACTIVE) {
        switch (state) {
        case STAGE_ENTRY_WAITING:
        case STAGE_ENTRY_ACTIVE:
            entry->state = state;
            return;
        }
    }
    entry->state = state;
    entry->pending = 0;
}
