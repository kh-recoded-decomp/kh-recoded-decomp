#include "nitro/types.h"

extern void UpdateActorSlotsAndBillboards(void);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void FieldScene_DrawHookNoop(void);
extern void UpdateActiveSubModeCamera(s32 value);

void DrawOv028FieldScene(void)
{
    UpdateActiveSubModeCamera(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    FieldScene_DrawHookNoop();
}
