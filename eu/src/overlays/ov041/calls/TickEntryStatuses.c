#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void ReleaseEntryStatusItem(u8 entryIndex);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);

/*
 * Counts an entry's timed statuses down (statuses 0 and 3 are not timed; status 0 at 2 drops to 1). When the
 * last one runs out its effect item goes, and a kind 0x15 entry plays its recovery effect.
 */
void TickEntryStatuses(u8 entryIndex)
{
    StageEntry *entry = &gMovieContextState->stageWork->entries[entryIndex];
    BOOL ended = FALSE;
    int i;
    BOOL active = FALSE;
    VecFx32 position;

    if (entry->statuses[0] == 2) {
        entry->statuses[0] = 1;
    }
    for (i = 0; i < STAGE_ENTRY_STATUS_COUNT; i++) {
        if (i == 3 || i == 0) {
            continue;
        }
        entry->statuses[i]--;
        if (entry->statuses[i] > 0) {
            active = TRUE;
        } else if (entry->statuses[i] == 0) {
            ended = TRUE;
        } else if (entry->statuses[i] < 0) {
            entry->statuses[i] = 0;
        }
    }
    if (ended && !active) {
        ReleaseEntryStatusItem(entryIndex);
        if (entry->kind == 0x15) {
            GetEntryPosition(&position, entry);
            SpawnStageItem(entry, 0x15, 0, 2, &position, FALSE);
            PlayStageSound(0xdd, 10, TRUE);
        }
    }
}
