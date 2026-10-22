#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void InvokeFieldModeOp428(void);
extern void SetStageEntryState(u8 entryIndex, int state);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void SetStageState(int state, BOOL runNow);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state 19 (retreat): sends every primary entry still in the fight back (entry state 9), waits until they
 * have all stepped back and no entry has anything left to play out, then sets work flag 0x8000 and moves on to
 * state 20. Every entry is updated each frame.
 */
void StageStateRetreat(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL allBack = TRUE;
    BOOL busy = FALSE;
    int i;
    int j;

    switch (work->stateStep) {
    case 0:
        InvokeFieldModeOp428();
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state != STAGE_ENTRY_OUT) {
                SetStageEntryState(i, 9);
                work->entries[i].flags |= STAGE_ENTRY_STEP_BACK;
            }
        }
        PlayStageSound(0x1a0, 7, TRUE);
        work->stateStep++;
    case 1:
        work->stateStep++;
    case 2:
        work->stateStep++;
    case 3:
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state == 9 && (work->entries[i].flags & STAGE_ENTRY_STEP_BACK)) {
                allBack = FALSE;
                break;
            }
        }
        if (!allBack) {
            break;
        }
        work->stateStep++;
    case 4:
        for (i = 0; i < work->entryCount; i++) {
            for (j = 0; j < 3; j++) {
                if (work->entries[i].orbBursts[j].active) {
                    busy = TRUE;
                    break;
                }
            }
        }
        if (!busy) {
            work->flags |= 0x8000;
            SetStageState(0x14, FALSE);
        }
        break;
    }
    for (i = 0; i < work->entryCount; i++) {
        UpdateStageEntry(i);
    }
}
