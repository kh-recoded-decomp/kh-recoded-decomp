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

extern SceneState *gAreaRewardSceneWork;
extern SharedScene *gMovieContextState;
extern u8 sOv040_RpgEfEcZ_020be248[];
extern BOOL UpdateMenuItemLoading(void);
extern void LoadFadeModel(int mode);
extern void HighlightSelectedMenuPanels(void);
extern void *CreateTaskObject(void *desc, void *arg);
extern int GetCurrentSceneEntryIndex(void);
extern u32 GetSceneEntryResourceId(int index);
extern u32 GetSceneResourceHandle(void);
extern void SetPanelHeaderText(const u16 *prefix, const u16 *name);
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
    if (gAreaRewardSceneWork->flags & 1) {
        u32 entryValue;
        HighlightSelectedMenuPanels();
        if ((int)gMovieContextState->handle == -1) {
            gMovieContextState->handle = CreateTaskObject(AREA_SCENE_DESCRIPTOR, NULL);
        }
        entryValue = GetSceneEntryResourceId(GetCurrentSceneEntryIndex());
        SetPanelHeaderText((const u16 *)GetSceneResourceHandle(), (const u16 *)entryValue);
    }
    InitSharedRecordAndDispatch(gAreaRewardSceneWork, sOv040_RpgEfEcZ_020be248, 1, 2);
    LoadDefaultProjectionValues(gAreaRewardSceneWork->projection);
    {
        VecFx32 offset = {0, 0, 0};
        state = gAreaRewardSceneWork;
        offset.z = state->topHeight - state->baseHeight - 0x1000;
        state->cameraOffset = offset;
    }
    selectJointAnimationBlend(state, 0, state->blendTarget, 0);
    selectJointAnimationBlend(gAreaRewardSceneWork, 2, gAreaRewardSceneWork->blendTarget, 0);
    InvokeSceneCallback();
    slotValue = GetSlotEntryValue(GetCurrentSceneEntryIndex());
    SetCachedSoundParams(slotValue, GetMenuItemValue(GetCurrentSceneEntryIndex()), 0x7f);
    gAreaRewardSceneWork->flags |= 0x8000;
    return 3;
}
