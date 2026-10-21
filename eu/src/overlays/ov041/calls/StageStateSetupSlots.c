#include "nitro/types.h"

extern int GetCurrentSceneEntrySlotId(void);
extern void func_ov001_02067d0c(int slot, BOOL arg);
extern void func_ov001_02067cd0(int slot, BOOL arg);
extern void ResetSceneSlots(void);
extern void SetStageState(int state, BOOL runNow);

/* Stage state 0: sets up every scene slot below the current one, then the current one, and moves on to state 1. */
void StageStateSetupSlots(void)
{
    int last = GetCurrentSceneEntrySlotId() - 1;
    int slot;

    for (slot = 0; slot < last; slot++) {
        func_ov001_02067d0c(slot, FALSE);
        func_ov001_02067cd0(slot, FALSE);
    }
    func_ov001_02067d0c(last, TRUE);
    func_ov001_02067cd0(last, TRUE);
    ResetSceneSlots();
    SetStageState(1, FALSE);
}
