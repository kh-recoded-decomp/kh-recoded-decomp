#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void ReleaseStageItem(StageResourceItem *item);

/*
 * Clears what an action left on an entry and its targets (timed press and per-action flags), then, unless the
 * action is still being shown, puts it back on its idle animation and frees its effect items.
 */
void ClearEntryActionState(StageEntry *entry)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *target;
    int kind;

    entry->flags &= ~STAGE_ENTRY_TIMED_PRESS;
    entry->flags &= ~0x10000;
    entry->flags &= ~0x100;
    entry->flags &= ~0x80;
    entry->flags &= ~STAGE_ENTRY_MISSED;
    for (i = 0; i < entry->targetCount; i++) {
        target = &work->entries[entry->targets[i]];
        target->flags &= ~STAGE_ENTRY_TIMED_PRESS;
        target->flags &= ~0x10000;
        target->flags &= ~0x20000;
        target->flags &= ~0x800000;
    }
    if (entry->kind == 0xfd && entry->actions[entry->actionIndex].kind == 5 && data_ov041_020cff48.unk00 != 3) {
        return;
    }
    kind = entry->actions[entry->actionIndex].kind;
    if (kind == 0 && data_ov041_020cff48.comboCount != 0) {
        return;
    }
    if (kind == 3 && data_ov041_020cff48.comboCount != 0) {
        return;
    }
    if (kind == 6 || kind == 10) {
        return;
    }
    if (kind == 2 && entry->kind == 0x17) {
        return;
    }
    if (!MatchesEitherSlotId(entry, entry->idleAnimation)) {
        SetSceneEntryAnimation(entry, entry->idleAnimation, 0, 0);
    }
    for (i = 0; i < 5; i++) {
        if (entry->effects[i] != NULL) {
            ReleaseStageItem(entry->effects[i]);
            entry->effects[i] = NULL;
        }
    }
}
