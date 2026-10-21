#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern StageEntryFunc gStageEntryStateHandlers[];
extern StageEntryFunc gStageEntryActionHandlers[];
extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern void UpdateEntryHpGauge(StageEntry *entry);
extern void UpdateEntryStatusIcon(StageEntry *entry);

/* Runs an entry's state handler for the frame (its action's handler while it acts), then its two updates. */
void UpdateStageEntry(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryFunc handler = gStageEntryStateHandlers[entry->state];

    if (handler == NULL) {
        gStageEntryActionHandlers[GetEntryAction(entry)->kind](entry->index);
    } else {
        handler(entry->index);
    }
    UpdateEntryHpGauge(entry);
    UpdateEntryStatusIcon(entry);
}
