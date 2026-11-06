extern void UpdateActiveSubModeCamera();
extern void DrawVisibleSceneSlots();
extern void RunFlaggedEventCallbacks();
extern void UpdateActorSlotsAndBillboards();
extern void FieldScene_DrawHookNoop();

void DrawOv029FieldScene(void)
{
    UpdateActiveSubModeCamera(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    FieldScene_DrawHookNoop();
}
