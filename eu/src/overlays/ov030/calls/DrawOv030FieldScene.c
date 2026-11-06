#include "nitro/types.h"

extern void UpdateActiveSubModeCamera(u32 arg);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void UpdateActorSlotsAndBillboards(void);
extern void FieldScene_DrawHookNoop(void);

void DrawOv030FieldScene(void)
{
    UpdateActiveSubModeCamera(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    FieldScene_DrawHookNoop();
}
