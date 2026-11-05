#include "nitro/types.h"

extern void UpdateActiveSubModeCamera(s32 flag);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void UpdateActorSlotsAndBillboards(void);
extern void func_ov001_020876d4(void);

void func_ov032_020bb36c(void) {
    UpdateActiveSubModeCamera(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    func_ov001_020876d4();
}
