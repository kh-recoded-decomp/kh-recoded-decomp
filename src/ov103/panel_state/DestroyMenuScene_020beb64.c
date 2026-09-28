#include "nitro/types.h"

typedef struct MenuScene MenuScene;

extern void ReleaseSlotPool_020bf64c(MenuScene *scene);
extern void ReleaseTextLayers_020bf32c(MenuScene *scene);
extern void FreeGraphicsResources_020bf074(MenuScene *scene);
extern void FreeArchiveFiles_020bef38(MenuScene *scene);
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);

void DestroyMenuScene_020beb64(MenuScene *scene)
{
    ReleaseSlotPool_020bf64c(scene);
    ReleaseTextLayers_020bf32c(scene);
    FreeGraphicsResources_020bf074(scene);
    FreeArchiveFiles_020bef38(scene);
    SetStateFlagBits_020bc688(0, 5);
}
