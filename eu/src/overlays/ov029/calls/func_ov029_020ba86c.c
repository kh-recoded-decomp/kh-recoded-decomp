extern void func_ov021_020af528();
extern void DrawVisibleSceneSlots();
extern void RunFlaggedEventCallbacks();
extern void UpdateActorSlotsAndBillboards();
extern void func_ov001_020876d4();

void func_ov029_020ba86c(void)
{
    func_ov021_020af528(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    func_ov001_020876d4();
}
