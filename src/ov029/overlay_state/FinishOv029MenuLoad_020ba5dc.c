#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

extern SceneState *data_ov029_020baba0;
extern BOOL UpdateMenuItemLoading_02067750(void);
extern BOOL AreAllListNodesReady_0207ed2c(void);
extern void func_ov001_020687b8(void);
extern void HighlightSelectedMenuPanels_0206781c(void);
extern void InvokeSceneCallback_020677fc(void);
extern int func_ov001_02067ed4(void);
extern int GetSlotEntryValue_02068000(int index);
extern int GetMenuItemValue_0206802c(int index);
extern void SetCachedSoundParams_0204dcec(u32 param1, u32 param2, u16 param3);
extern void InvokeListNodeCallbacks_0207eff0(void);
extern void SetSlotConfigFlag38_02067870(void);
extern u32 func_ov001_020681d4(int index);
extern u32 func_ov001_020681c4(void);
extern void func_ov001_0207b0c0(u32 first, u32 second);

int FinishOv029MenuLoad_020ba5dc(void)
{
    int slotValue;
    u32 entryValue;

    if (!UpdateMenuItemLoading_02067750() || !AreAllListNodesReady_0207ed2c()) {
        return -1;
    }
    func_ov001_020687b8();
    HighlightSelectedMenuPanels_0206781c();
    InvokeSceneCallback_020677fc();
    slotValue = GetSlotEntryValue_02068000(func_ov001_02067ed4());
    SetCachedSoundParams_0204dcec(slotValue, GetMenuItemValue_0206802c(func_ov001_02067ed4()), 0x7f);
    InvokeListNodeCallbacks_0207eff0();
    SetSlotConfigFlag38_02067870();
    entryValue = func_ov001_020681d4(func_ov001_02067ed4());
    func_ov001_0207b0c0(func_ov001_020681c4(), entryValue);
    data_ov029_020baba0->flags |= 0x8000;
    return 4;
}
