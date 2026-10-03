#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xa4];
    VecFx32 cameraOffset;
    u8 pad_b0[0x28];
    u8 blendTarget[0x2c];
    u8 projection[0xc];
    fx32 baseHeight;
    u8 pad_114[0x18];
    fx32 topHeight;
    u8 pad_130[0xc];
    u16 flags;
} SceneState;

typedef struct {
    u8 pad_00[0x14];
    void *handle;
} SharedScene;

extern SceneState *data_ov040_020be260;
extern SharedScene *data_ov035_020bc4e0;
extern u8 data_ov035_020bc4c8[];
extern u8 data_ov040_020be228[];
extern BOOL UpdateMenuItemLoading_02067750(void);
extern void func_ov035_020bb50c(int mode);
extern void HighlightSelectedMenuPanels_0206781c(void);
extern void *func_0202a448(void *desc, void *arg);
extern int func_ov001_02067ed4(void);
extern u32 func_ov001_020681d4(int index);
extern u32 func_ov001_020681c4(void);
extern void func_ov001_0207b0c0(u32 first, u32 second);
extern void func_0202ecf8(void *state, void *desc, int a, int b);
extern void LoadDefaultProjectionValues_0202a7b4(void *projection);
extern void selectJointAnimationBlend_0202f2cc(void *state, int joint, void *target, int flags);
extern void InvokeSceneCallback_020677fc(void);
extern int GetSlotEntryValue_02068000(int index);
extern int GetMenuItemValue_0206802c(int index);
extern void SetCachedSoundParams_0204dcec(u32 param1, u32 param2, u16 param3);

int FinishAreaSceneLoad_020bcd4c(void) {
    SceneState *state;
    int slotValue;

    if (UpdateMenuItemLoading_02067750() == FALSE) {
        return -1;
    }
    func_ov035_020bb50c(0);
    if (data_ov040_020be260->flags & 1) {
        u32 entryValue;
        HighlightSelectedMenuPanels_0206781c();
        if ((int)data_ov035_020bc4e0->handle == -1) {
            data_ov035_020bc4e0->handle = func_0202a448(data_ov035_020bc4c8, NULL);
        }
        entryValue = func_ov001_020681d4(func_ov001_02067ed4());
        func_ov001_0207b0c0(func_ov001_020681c4(), entryValue);
    }
    func_0202ecf8(data_ov040_020be260, data_ov040_020be228, 1, 2);
    LoadDefaultProjectionValues_0202a7b4(data_ov040_020be260->projection);
    {
        VecFx32 offset = {0, 0, 0};
        state = data_ov040_020be260;
        offset.z = state->topHeight - state->baseHeight - 0x1000;
        state->cameraOffset = offset;
    }
    selectJointAnimationBlend_0202f2cc(state, 0, state->blendTarget, 0);
    selectJointAnimationBlend_0202f2cc(data_ov040_020be260, 2, data_ov040_020be260->blendTarget, 0);
    InvokeSceneCallback_020677fc();
    slotValue = GetSlotEntryValue_02068000(func_ov001_02067ed4());
    SetCachedSoundParams_0204dcec(slotValue, GetMenuItemValue_0206802c(func_ov001_02067ed4()), 0x7f);
    data_ov040_020be260->flags |= 0x8000;
    return 3;
}
