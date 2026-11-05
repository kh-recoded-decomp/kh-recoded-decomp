#include "nitro/types.h"

extern s32 UpdateMenuItemLoading(void);
extern BOOL IsSceneState1(void);
extern BOOL IsSceneState4(void);
extern void LoadFadeModel(int mode);
extern void InvokeSceneCallback(void);
extern int GetCurrentSceneEntryIndex(void);
extern int GetSlotEntryValue(int index);
extern int GetMenuItemValue(int index);
extern void SetCachedSoundParams(u32 param1, u32 param2, u16 param3);
extern void ForwardToActiveService_02087f10(void);
extern void SetStageState(int state, BOOL runNow);

/* Stage state 1: once the menu items are loaded and the scene is free, sets the music up and moves on to state 2. */
void StageStateStartMusic(void)
{
    int slotValue;

    if (UpdateMenuItemLoading() && !IsSceneState1() && !IsSceneState4()) {
        LoadFadeModel(1);
        InvokeSceneCallback();
        slotValue = GetSlotEntryValue(GetCurrentSceneEntryIndex());
        SetCachedSoundParams(slotValue, GetMenuItemValue(GetCurrentSceneEntryIndex()), 0x7f);
        ForwardToActiveService_02087f10();
        SetStageState(2, TRUE);
    }
}
