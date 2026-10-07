#include "nitro/types.h"

#define func_ov001_020681c4 GetSceneResourceHandle
#define func_ov001_020681d4 GetSceneEntryResourceId

extern u32 data_ov030_020bd020;
extern s32 UpdateMenuItemLoading(void);
extern void func_ov001_020687b8(void);
extern void HighlightSelectedMenuPanels(void);
extern void InvokeSceneCallback(void);
extern void func_ov001_02067ed4(void);
extern u32 GetSlotEntryValue(void);
extern u32 GetMenuItemValue(void);
extern void SetCachedSoundParams(u32 a, u32 b, u32 c);
extern void InvokeListNodeCallbacks(void);
extern void QueueAreaSoundArchives(void);
extern u32 func_ov001_020681d4(void);
extern u32 func_ov001_020681c4(void);
extern void func_ov001_0207b0c0(u32 a, u32 b);

u32 func_ov030_020ba62c(void)
{
    s32 ready;
    u32 valueA;
    u32 valueB;

    ready = UpdateMenuItemLoading();
    if (ready == 0) {
        return 0xffffffff;
    }
    func_ov001_020687b8();
    HighlightSelectedMenuPanels();
    InvokeSceneCallback();
    func_ov001_02067ed4();
    valueA = GetSlotEntryValue();
    func_ov001_02067ed4();
    valueB = GetMenuItemValue();
    SetCachedSoundParams(valueA, valueB, 0x7f);
    InvokeListNodeCallbacks();
    QueueAreaSoundArchives();
    func_ov001_02067ed4();
    valueA = func_ov001_020681d4();
    valueB = func_ov001_020681c4();
    func_ov001_0207b0c0(valueB, valueA);
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) | 0x8000;
    return 5;
}
