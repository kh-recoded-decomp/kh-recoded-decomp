#include "nitro/types.h"

typedef struct SceneResources {
    u8 pad_00[0x04];
    u8 objectLists[3][0x34];
    u8 pad_a0[0x24];
    void *workBuffer;
    u8 pad_c8[0x08];
    u8 resourceNode[1];
} SceneResources;

extern void *func_ov039_020bc18c(void);
extern void SweepElements_020b831c(void *elementSystem);
extern void FreePointerIfSet_020ba294(void **ptr);
extern BOOL DestroyFndObjectList_020014f0(void *container);
extern void ReleaseResourceAndDetach_0202eee8(void *object);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void NNS_GfdResetFrmPlttVramState_02013d74(void);
extern void func_02006d3c(u32 value);

void TeardownSceneResources_020bf9a4(SceneResources *scene) {
    SweepElements_020b831c(func_ov039_020bc18c());
    FreePointerIfSet_020ba294(&scene->workBuffer);
    DestroyFndObjectList_020014f0(scene->objectLists[0]);
    DestroyFndObjectList_020014f0(scene->objectLists[1]);
    DestroyFndObjectList_020014f0(scene->objectLists[2]);
    ReleaseResourceAndDetach_0202eee8(scene->resourceNode);
    NNS_GfdResetFrmTexVramState_0201391c();
    NNS_GfdResetFrmPlttVramState_02013d74();
    func_02006d3c(0);
}
