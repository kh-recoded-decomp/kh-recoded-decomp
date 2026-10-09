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

#define AREA_SCENE_DESCRIPTOR ((void *)0x020bc4e8)

extern SceneState *data_ov040_020be280;
extern SharedScene *gMovieContextState;
extern u8 sOv040_RpgEfEcZ_020be248[];
extern BOOL UpdateMenuItemLoading(void);
extern void LoadFadeModel(int mode);
extern void HighlightSelectedMenuPanels(void);
extern void *func_0202a45c(void *desc, void *arg);
extern int func_ov001_02067ed4(void);
extern u32 GetSceneEntryResourceId(int index);
extern u32 GetSceneResourceHandle(void);
extern void func_ov001_0207b0c0(u32 first, u32 second);
extern void InitSharedRecordAndDispatch(void *state, void *desc, int a, int b);
extern void LoadDefaultProjectionValues(void *projection);
extern void selectJointAnimationBlend(void *state, int joint, void *target, int flags);
extern void InvokeSceneCallback(void);
extern int GetSlotEntryValue(int index);
extern int GetMenuItemValue(int index);
extern void SetCachedSoundParams(u32 param1, u32 param2, u16 param3);

int FinishAreaSceneLoad(void)
{
    SceneState *state;
    int slotValue;

    if (UpdateMenuItemLoading() == FALSE) {
        return -1;
    }
    LoadFadeModel(0);
    if (data_ov040_020be280->flags & 1) {
        u32 entryValue;
        HighlightSelectedMenuPanels();
        if ((int)gMovieContextState->handle == -1) {
            gMovieContextState->handle = func_0202a45c(AREA_SCENE_DESCRIPTOR, NULL);
        }
        entryValue = GetSceneEntryResourceId(func_ov001_02067ed4());
        func_ov001_0207b0c0(GetSceneResourceHandle(), entryValue);
    }
    InitSharedRecordAndDispatch(data_ov040_020be280, sOv040_RpgEfEcZ_020be248, 1, 2);
    LoadDefaultProjectionValues(data_ov040_020be280->projection);
    {
        VecFx32 offset = {0, 0, 0};
        state = data_ov040_020be280;
        offset.z = state->topHeight - state->baseHeight - 0x1000;
        state->cameraOffset = offset;
    }
    selectJointAnimationBlend(state, 0, state->blendTarget, 0);
    selectJointAnimationBlend(data_ov040_020be280, 2, data_ov040_020be280->blendTarget, 0);
    InvokeSceneCallback();
    slotValue = GetSlotEntryValue(func_ov001_02067ed4());
    SetCachedSoundParams(slotValue, GetMenuItemValue(func_ov001_02067ed4()), 0x7f);
    data_ov040_020be280->flags |= 0x8000;
    return 3;
}
