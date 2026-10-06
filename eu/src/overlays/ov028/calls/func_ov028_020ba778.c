#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern void SetCachedSoundParams(u32 param1, u32 param2, u16 param3);
extern s32 UpdateMenuItemLoading(void);
extern void InvokeSceneCallback(void);
extern void HighlightSelectedMenuPanels(void);
extern void QueueAreaSoundArchives(void);
extern u32 func_ov001_02067ed4(void);
extern u32 GetSlotEntryValue(void);
extern u32 GetMenuItemValue(void);
extern u32 func_ov001_020681c4(void);
extern u32 func_ov001_020681d4(void);
extern void func_ov001_020687b8(s32 value);
extern void func_ov001_0207b0c0(u32 param1, u32 param2);
extern void InvokeListNodeCallbacks(void);

u32 func_ov028_020ba778(void)
{
    s32 value = UpdateMenuItemLoading();
    u32 arg1;
    u32 arg2;

    if (value != 0) {
        func_ov001_020687b8(value);
        HighlightSelectedMenuPanels();
        InvokeSceneCallback();
        func_ov001_02067ed4();
        arg1 = GetSlotEntryValue();
        func_ov001_02067ed4();
        arg2 = GetMenuItemValue();
        SetCachedSoundParams(arg1, arg2, 0x7f);
        InvokeListNodeCallbacks();
        QueueAreaSoundArchives();
        func_ov001_02067ed4();
        arg1 = func_ov001_020681d4();
        arg2 = func_ov001_020681c4();
        func_ov001_0207b0c0(arg2, arg1);
        *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) | 0x8000;
        return 5;
    }
    return 0xffffffff;
}
