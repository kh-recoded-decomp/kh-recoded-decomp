#include "nitro/types.h"

extern int GetCurrentSceneEntrySlotId(void);
extern void SetSceneSlotResourceLoadingEnabled(int slot, BOOL arg);
extern void SetSceneSlotDrawingEnabled(int slot, BOOL arg);
extern void ResetSceneSlots(void);
extern void SetStageState(int state, BOOL runNow);

/* Stage state 0: sets up every scene slot below the current one, then the current one, and moves on to state 1. */
void StageStateSetupSlots(void)
{
    int last = GetCurrentSceneEntrySlotId() - 1;
    int slot;

    for (slot = 0; slot < last; slot++) {
        SetSceneSlotResourceLoadingEnabled(slot, FALSE);
        SetSceneSlotDrawingEnabled(slot, FALSE);
    }
    SetSceneSlotResourceLoadingEnabled(last, TRUE);
    SetSceneSlotDrawingEnabled(last, TRUE);
    ResetSceneSlots();
    SetStageState(1, FALSE);
}
