#include "nitro/types.h"

extern void func_ov021_020af528(s32 flag);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void UpdateActorSlotsAndBillboards(void);
extern void func_ov001_020876d4(void);

void func_ov032_020bb36c(void) {
    func_ov021_020af528(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    func_ov001_020876d4();
}
