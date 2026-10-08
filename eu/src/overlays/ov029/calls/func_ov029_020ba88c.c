extern void UpdateSceneAnimsAndCaption();
extern void UpdateFieldObjectStates();
extern void UpdatePartyEntries();
extern void StageManager_Update();
extern void UpdatePrizeOrbs();
extern void ActorRegistry_ForEachCallback();

void func_ov029_020ba88c(int mode)
{
    if (mode == 0) {
        UpdateSceneAnimsAndCaption(0x1000);
        UpdateFieldObjectStates(0x1000);
    }
    UpdatePartyEntries(0x1000);
    if (mode == 0) {
        StageManager_Update(0x1000);
        UpdatePrizeOrbs();
    }
    ActorRegistry_ForEachCallback(0x1000);
}
