#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern BOOL HasEntryWithClearState(BOOL enemies);
extern BOOL HasActionInRange(StageEntry *entry);
extern int PickTargetInRange(StageEntry *entry, int range);
extern void FillActionTargets(StageEntry *entry);

/*
 * Picks the entry its action aims at (mainTarget) and fills its targets (FillActionTargets): nobody left to
 * aim at keeps it on itself; a player entry in a stage with flags 0x20 aims at the kind 0x17 entry once no kind
 * 0 secondary entry is left (flag 0x400000) or else at the first enemy; otherwise the target is kept unless the
 * action kind or a target that is out calls for a new one in range (PickTargetInRange).
 */
void ChooseEntryMainTarget(StageEntry *entry)
{
    StageWork *stage;
    StageWork *work;
    BOOL found;
    u8 target;
    BOOL picked;
    int i;

    work = gMovieContextState->stageWork;
    found = picked = FALSE;
    if (!HasEntryWithClearState(entry->flags & STAGE_ENTRY_ENEMY)) {
        entry->mainTarget = entry->index;
        return;
    }
    if (!(entry->flags & STAGE_ENTRY_ENEMY) && (work->flags & 0x20)) {
        stage = work;
        if (stage->flags & 0x400000) {
            for (i = stage->primaryCount; i < stage->entryCount; i++) {
                if (stage->entries[i].kind == 0 && stage->entries[i].state != STAGE_ENTRY_OUT) {
                    found = TRUE;
                }
            }
            if (!found) {
                for (i = 0; i < stage->entryCount; i++) {
                    if (stage->entries[i].kind == 0x17) {
                        entry->mainTarget = i;
                        entry->targetCount = 1;
                        entry->targets[0] = i;
                        picked = TRUE;
                    }
                }
            }
        } else {
            for (i = 0; i < stage->entryCount; i++) {
                if (stage->entries[i].flags & STAGE_ENTRY_ENEMY) {
                    entry->mainTarget = i;
                    picked = TRUE;
                    entry->targetCount = 1;
                    entry->targets[0] = entry->mainTarget;
                    break;
                }
            }
        }
        if (picked) {
            FillActionTargets(entry);
            return;
        }
    }
    if (!HasActionInRange(entry)) {
        entry->mainTarget = entry->index;
        return;
    }
    if (entry->mainTarget != entry->index) {
        switch (entry->actions[entry->actionIndex].kind) {
        case 4:
        case 5:
        case 6:
        case 10:
            target = PickTargetInRange(entry, entry->actions[entry->actionIndex].range);
            break;
        case 2:
            if (entry->kind == 0x17) {
                target = PickTargetInRange(entry, entry->actions[entry->actionIndex].range);
            }
            break;
        default:
            if (work->entries[entry->mainTarget].state != STAGE_ENTRY_OUT) {
                target = entry->mainTarget;
            } else {
                target = PickTargetInRange(entry, entry->actions[entry->actionIndex].range);
            }
            break;
        }
    } else {
        target = PickTargetInRange(entry, entry->actions[entry->actionIndex].range);
    }
    if (target != entry->index) {
        entry->mainTarget = target;
        FillActionTargets(entry);
    }
}
