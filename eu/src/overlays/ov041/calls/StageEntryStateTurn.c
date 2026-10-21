#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define STAGE_ENTRY_ACTING 4

extern const fx32 gStageTurnEffectHeights[];
extern BOOL HasActionInRange(StageEntry *entry);
extern void SetEntryState(StageEntry *entry, int state);
extern void ChooseEntryAction(u8 entryIndex);
extern const u16 *GetFieldChunkEntry(int index);
extern void ShowFieldMessageLine_02072ad0(int kind, ...);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern s32 GetHudLabelId(int labelIndex);
extern const u16 *GetModePrimaryMessage(int mode);
extern void HideHudCaption(void);
extern void FinishEntryAction(StageEntry *entry);

static inline VecFx32 GroundPosition(StageEntry *entry)
{
    VecFx32 position;

    GetPositionAboveGround(&position, entry);
    return position;
}

static inline void SpawnHealEffect(StageEntry *entry)
{
    VecFx32 position;

    GetPositionAboveGround(&position, entry);
    entry->effects[0] = SpawnStageItem(entry, 0xff, 0x13, 0, &position, FALSE);
    PlayStageSound(0x1a0, 14, TRUE);
}

/*
 * Entry state 2 (its turn): goes back to waiting when it has nothing in range (players get a pass under work
 * flag 0x20), otherwise picks its action, names it for enemies and shows the turn effect at the current
 * height. Under status 0 at 2 it only shows the heal effect and ends its turn; otherwise it starts acting.
 */
void StageEntryStateTurn(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    int message;

    switch (entry->stateStep) {
    case 0:
        entry->stateStep++;
    case 1:
        if (!HasActionInRange(entry) && ((entry->flags & STAGE_ENTRY_ENEMY) || !(work->flags & 0x20))) {
            SetEntryState(entry, STAGE_ENTRY_WAITING);
            return;
        }
        ChooseEntryAction(entry->index);
        if (entry->flags & STAGE_ENTRY_ENEMY) {
            if (entry->kind != 0xfd) {
                message = entry->actions[entry->actionIndex].effectArg;
            } else {
                switch (entry->actions[entry->actionIndex].kind) {
                case 0:
                    message = 0x25;
                    break;
                case 5:
                    message = 0x26;
                    break;
                default:
                    message = 0;
                    break;
                }
            }
            ShowFieldMessageLine_02072ad0(0x11, GetFieldChunkEntry(message));
        }
        {
            VecFx32 start = GroundPosition(entry);

            start.y = gStageTurnEffectHeights[work->shadowHeightIndex];
            entry->effects[0] = SpawnStageItem(entry, 0xff, 0, 0, &start, FALSE);
        }
        PlayStageSound(0x1a0, 1, TRUE);
        entry->stateStep++;
    case 2:
        if (entry->effects[0]->flags & STAGE_ITEM_IN_USE) {
            break;
        }
        if (entry->statuses[0] == 2) {
            SpawnHealEffect(entry);
        }
        entry->stateStep++;
    case 3:
        if (entry->statuses[0] == 2) {
            if (entry->effects[0]->flags & STAGE_ITEM_IN_USE) {
                ShowFieldMessageLine_02072ad0(0xb, GetHudLabelId(0xcb), GetModePrimaryMessage(0));
                return;
            }
            HideHudCaption();
            FinishEntryAction(entry);
            return;
        }
        SetEntryState(entry, STAGE_ENTRY_ACTING);
        break;
    }
}
