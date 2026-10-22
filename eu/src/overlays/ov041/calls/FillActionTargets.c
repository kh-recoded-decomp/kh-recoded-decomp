#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern StageEntry *FindStageEntryBySceneSlot(int sceneSlot);

/* The magic action kind (its power comes from magic) and the effect that also reaches entries that are out. */
#define ACTION_KIND_MAGIC 0xc
#define EFFECT_REACHES_OUT 0xeb

/*
 * Fills entry->targets with the entries its action hits around its main target, by the action's target kind, and
 * shows their hp. Only entries still in the fight count, except for the STAGE_TARGET_ONE_EVEN_OUT kind and the
 * magic effect 0xeb.
 */
void FillActionTargets(StageEntry *entry)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntryAction *action = GetEntryAction(entry);
    u8 mainTarget = entry->mainTarget;
    int i = 0;
    StageEntry *main;

    entry->targetCount = 0;
    main = &work->entries[mainTarget];
    switch (action->targetKind) {
    case STAGE_TARGET_ONE:
        if (work->entries[mainTarget].state != STAGE_ENTRY_OUT) {
            entry->targets[entry->targetCount] = mainTarget;
            entry->targetCount++;
            main->flags |= STAGE_ENTRY_SHOW_HP;
        }
        break;
    case STAGE_TARGET_ROW:
        for (; i < work->entryCount; i++) {
            if (FindStageEntryBySceneSlot(work->entries[i].sceneSlot) != NULL) {
                if (work->entries[entry->mainTarget].sceneSlot / 3 == work->entries[i].sceneSlot / 3 &&
                    work->entries[i].state != STAGE_ENTRY_OUT) {
                    entry->targets[entry->targetCount] = i;
                    entry->targetCount++;
                    work->entries[i].flags |= STAGE_ENTRY_SHOW_HP;
                }
            }
        }
        break;
    case STAGE_TARGET_COLUMN: /* columns run through both sides: only the main target's */
        for (; i < work->entryCount; i++) {
            if (FindStageEntryBySceneSlot(work->entries[i].sceneSlot) != NULL) {
                if (work->entries[entry->mainTarget].sceneSlot % 3 == work->entries[i].sceneSlot % 3 &&
                    (((main->flags & STAGE_ENTRY_ENEMY) && work->entries[i].sceneSlot >= 3) ||
                     (!(main->flags & STAGE_ENTRY_ENEMY) && work->entries[i].sceneSlot < 3)) &&
                    work->entries[i].state != STAGE_ENTRY_OUT) {
                    entry->targets[entry->targetCount] = i;
                    entry->targetCount++;
                    work->entries[i].flags |= STAGE_ENTRY_SHOW_HP;
                }
            }
        }
        break;
    case STAGE_TARGET_ALL:
        for (; i < work->entryCount; i++) {
            if ((((main->flags & STAGE_ENTRY_ENEMY) && work->entries[i].sceneSlot >= 3) ||
                 (!(main->flags & STAGE_ENTRY_ENEMY) && work->entries[i].sceneSlot < 3)) &&
                work->entries[i].state != STAGE_ENTRY_OUT) {
                entry->targets[entry->targetCount] = i;
                entry->targetCount++;
                work->entries[i].flags |= STAGE_ENTRY_SHOW_HP;
            }
        }
        break;
    case STAGE_TARGET_ONE_PRIMARY:
        if (main->state != STAGE_ENTRY_OUT) {
            entry->targets[entry->targetCount] = mainTarget;
            entry->targetCount++;
            main->flags |= STAGE_ENTRY_SHOW_HP;
        }
        break;
    case STAGE_TARGET_ALL_PRIMARY:
        for (; i < work->primaryCount; i++) {
            if (work->entries[i].state != STAGE_ENTRY_OUT || (action->kind == ACTION_KIND_MAGIC && action->effect == EFFECT_REACHES_OUT)) {
                entry->targets[entry->targetCount] = i;
                entry->targetCount++;
                work->entries[i].flags |= STAGE_ENTRY_SHOW_HP;
            }
        }
        break;
    case STAGE_TARGET_ONE_EVEN_OUT:
        entry->targets[entry->targetCount] = mainTarget;
        entry->targetCount++;
        main->flags |= STAGE_ENTRY_SHOW_HP;
        break;
    }
}
