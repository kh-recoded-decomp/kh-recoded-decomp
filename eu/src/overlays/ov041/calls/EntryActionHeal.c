#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded the way the converter of the original tools did. */
#define FRAME_TO_FX32(x) ((x) > 0 ? (fx32)((f32)((x) << FX32_SHIFT) + 0.5f) : (fx32)((f32)((x) << FX32_SHIFT) - 0.5f))

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern int func_0202a9e4(u16 range);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void MI_Copy48B(const void *src, void *dest);
extern void func_ov041_020c4aa0(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);

/*
 * Action handler for a heal: aims at a random hurt secondary entry other than itself (itself when none is),
 * shows that entry's hp, plays the animation and on its effect frame shows the heal item over itself, then
 * resolves the hit (func_ov041_020c4aa0, ApplyActionToTargets) and ends the action.
 */
void EntryActionHeal(u8 entryIndex)
{
    VecFx32 position;
    StageEntryAction *action;
    BOOL allHealthy;
    BOOL found;
    StageWork *work;
    StageEntry *entry;
    int frame;
    int start;
    int i;
    StageEntry *other;
    StageResourceItem *item;

    work = gMovieContextState->stageWork;
    entry = &work->entries[entryIndex];
    action = GetEntryAction(entry);
    frame = GetEntryAnimationFrame(entry);

    switch (entry->stateStep) {
    case 0:
        entry->stateStep++;
    case 1:
        allHealthy = TRUE;
        for (i = 0; i < work->secondaryCount; i++) {
            other = &work->entries[i + work->primaryCount];
            if (other != NULL && other != entry && other->state != STAGE_ENTRY_OUT && other->hp < other->maxHp) {
                allHealthy = FALSE;
                break;
            }
        }
        if (allHealthy) {
            entry->mainTarget = entry->index;
        } else {
            found = FALSE;
            start = func_0202a9e4(work->secondaryCount * 1000) / 1000;
            for (i = 0; i < work->secondaryCount; i++) {
                other = &work->entries[start + work->primaryCount];
                if (entry->index != start && other->state != STAGE_ENTRY_OUT && other->hp < other->maxHp) {
                    entry->mainTarget = start + work->primaryCount;
                    found = TRUE;
                    break;
                }
                start++;
                if (start == work->secondaryCount) {
                    start = 0;
                }
            }
            if (!found) {
                entry->mainTarget = entry->index;
            }
        }
        entry->targetCount = 1;
        entry->targets[0] = entry->mainTarget;
        other = &work->entries[entry->mainTarget];
        other->flags |= STAGE_ENTRY_SHOW_HP;
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        entry->stateStep++;
    case 2:
        if (frame < FRAME_TO_FX32(action->effectFrame)) {
            break;
        }
        GetEntryOverheadPosition(&position, entry);
        item = SpawnStageItem(entry, action->healEffectCategory, action->healEffectIndex, action->healEffectAnimation,
                              &position, FALSE);
        if (item != NULL) {
            MI_Copy48B(&entry->slot.node.rotation, &item->model.rotation);
        }
        item->model.position.x += FX32_ONE;
        item->model.position.y += FX32_ONE / 2;
        entry->stateStep++;
    case 3:
        func_ov041_020c4aa0(entry, &entry->hit);
        ApplyActionToTargets(entry);
        entry->stateStep++;
    case 4:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        FinishEntryAction(entry);
        break;
    }
}
