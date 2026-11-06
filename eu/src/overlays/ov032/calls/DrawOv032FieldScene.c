#include "nitro/types.h"

extern void UpdateActiveSubModeCamera(s32 flag);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void UpdateActorSlotsAndBillboards(void);
extern void FieldScene_DrawHookNoop(void);

void DrawOv032FieldScene(void) {
    UpdateActiveSubModeCamera(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    FieldScene_DrawHookNoop();
}
