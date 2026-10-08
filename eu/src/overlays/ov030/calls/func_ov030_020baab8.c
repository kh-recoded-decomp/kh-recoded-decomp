#include "nitro/types.h"

extern void func_ov021_020af528(u32 arg);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void UpdateActorSlotsAndBillboards(void);
extern void func_ov001_020876d4(void);

void func_ov030_020baab8(void)
{
    func_ov021_020af528(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    func_ov001_020876d4();
}
