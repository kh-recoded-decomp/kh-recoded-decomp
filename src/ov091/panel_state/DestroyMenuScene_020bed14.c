#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xca08];
    void *task;
} MenuScene;

extern void DestroyTask_020c27cc(void *task);
extern void ReleaseListRecords_020bfa2c(MenuScene *scene);
extern void ReleaseListPanels_020bf87c(MenuScene *scene);
extern void ReleaseTextLayers_020bf4e4(MenuScene *scene);
extern void FreeGraphicsResources_020bf3e0(MenuScene *scene);
extern void FreeMessageBuffers_020bf1d8(MenuScene *scene);
extern void func_02050a44(void);
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);

void DestroyMenuScene_020bed14(MenuScene *scene)
{
    DestroyTask_020c27cc(scene->task);
    ReleaseListRecords_020bfa2c(scene);
    ReleaseListPanels_020bf87c(scene);
    ReleaseTextLayers_020bf4e4(scene);
    FreeGraphicsResources_020bf3e0(scene);
    FreeMessageBuffers_020bf1d8(scene);
    func_02050a44();
    SetStateFlagBits_020bc688(0, 5);
}
