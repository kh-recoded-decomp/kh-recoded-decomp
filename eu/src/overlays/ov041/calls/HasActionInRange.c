#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define STAGE_HEALER_KIND 7

extern int func_ov041_020c2c1c(StageEntry *entry);

/*
 * TRUE when an entry still in the fight has an action reaching as far as it needs (func_ov041_020c2c1c). A
 * healer (kind 7) has none while every secondary entry still in the fight is at full hp.
 */
BOOL HasActionInRange(StageEntry *entry)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL usable = FALSE;
    int i;
    int needed;
    BOOL allHealthy;
    StageEntry *other;

    if (entry->state == STAGE_ENTRY_OUT) {
        return usable;
    }
    needed = func_ov041_020c2c1c(entry);
    for (i = 0; i < entry->actionCount; i++) {
        if (entry->actions[i].range >= needed) {
            usable = TRUE;
            break;
        }
    }
    if (entry->kind == STAGE_HEALER_KIND) {
        allHealthy = TRUE;
        for (i = 0; i < work->secondaryCount; i++) {
            other = &work->entries[i + work->primaryCount];
            if (other != NULL && other->state != STAGE_ENTRY_OUT && other->hp < other->maxHp) {
                allHealthy = FALSE;
                break;
            }
        }
        if (allHealthy) {
            usable = FALSE;
        }
    }
    return usable;
}
