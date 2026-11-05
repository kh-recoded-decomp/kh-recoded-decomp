extern void UpdateActiveSubModeCamera();
extern void DrawVisibleSceneSlots();
extern void RunFlaggedEventCallbacks();
extern void UpdateActorSlotsAndBillboards();
extern void func_ov001_020876d4();

void func_ov029_020ba86c(void)
{
    UpdateActiveSubModeCamera(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    func_ov001_020876d4();
}
