#include "nitro/types.h"

extern void UpdateActorSlotsAndBillboards(void);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void func_ov001_020876d4(void);
extern void UpdateActiveSubModeCamera(s32 value);

void DrawOv028FieldScene(void)
{
    UpdateActiveSubModeCamera(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    func_ov001_020876d4();
}
