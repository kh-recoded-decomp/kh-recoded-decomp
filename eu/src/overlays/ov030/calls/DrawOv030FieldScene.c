#include "nitro/types.h"

extern void UpdateActiveSubModeCamera(u32 arg);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void UpdateActorSlotsAndBillboards(void);
extern void func_ov001_020876d4(void);

void DrawOv030FieldScene(void)
{
    UpdateActiveSubModeCamera(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    func_ov001_020876d4();
}
