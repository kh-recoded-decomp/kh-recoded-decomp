#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void ShowStageHudMessage(u8 kind, ...);
extern BOOL IsStageHudMessageShowing(void);
extern void UpdateStageEntry(u8 entryIndex);
extern void SetStageState(int state, BOOL runNow);

/*
 * Stage state 5: shows the opening HUD messages one after the other (which ones depends on the intro kind and
 * value; value 2 puts message 2 up twice, as the case falls through), updating the entries until every one of
 * them has left state 0, then sets work flag 1 and moves on to state 8.
 */
void StageStateIntro(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL ready = TRUE;
    BOOL shown = FALSE;
    int i;

    switch (work->introStep) {
    case 0:
        work->introStep++;
    case 1:
        switch (work->introKind) {
        case 2:
            ShowStageHudMessage(1);
            break;
        case 3:
            ShowStageHudMessage(0);
            break;
        }
        work->introStep++;
        break;
    case 2:
        if (IsStageHudMessageShowing()) {
            break;
        }
        switch (work->introValue) {
        case 0:
        case 1:
            break;
        case 2:
            ShowStageHudMessage(2, work->introValue);
        case 3:
            ShowStageHudMessage(2, work->introValue);
            break;
        }
        work->introStep++;
        break;
    case 3:
        if (IsStageHudMessageShowing()) {
            break;
        }
        switch (work->introValue) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            ShowStageHudMessage(3, work->introValue);
            break;
        }
        work->introStep++;
        break;
    case 4:
        if (!IsStageHudMessageShowing()) {
            shown = TRUE;
        }
        break;
    }
    if (work->stateStep == 0) {
        for (i = 0; i < work->entryCount; i++) {
            if (work->entries[i].state == 0) {
                ready = FALSE;
                break;
            }
        }
        if (!ready) {
            for (i = 0; i < work->entryCount; i++) {
                UpdateStageEntry(i);
            }
        }
    }
    if (ready && shown) {
        work->introStep = 0;
        work->flags |= 1;
        SetStageState(8, TRUE);
    }
}
