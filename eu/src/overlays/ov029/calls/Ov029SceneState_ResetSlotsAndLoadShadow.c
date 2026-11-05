extern void ResetSceneSlots();
extern void ObjectManager_LoadShadowModel();

int Ov029SceneState_ResetSlotsAndLoadShadow(void)
{
    ResetSceneSlots();
    ObjectManager_LoadShadowModel();
    return 3;
}
