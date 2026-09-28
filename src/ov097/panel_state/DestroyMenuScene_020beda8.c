#include "nitro/types.h"

typedef struct MenuScene MenuScene;

extern MenuScene *g_menuScene_020c2520;
extern void func_ov097_020c0edc(MenuScene *scene);
extern void func_ov097_020c0d20(MenuScene *scene);
extern void ReleaseSlotPools_020bff44(MenuScene *scene);
extern void ReleaseTextLayers_020bfac8(MenuScene *scene);
extern void FreeGraphicsResources_020bf82c(MenuScene *scene);
extern void FreeMessageBuffers_020bf6ec(MenuScene *scene);
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);

void DestroyMenuScene_020beda8(MenuScene *scene)
{
    func_ov097_020c0edc(scene);
    func_ov097_020c0d20(scene);
    ReleaseSlotPools_020bff44(scene);
    ReleaseTextLayers_020bfac8(scene);
    FreeGraphicsResources_020bf82c(scene);
    FreeMessageBuffers_020bf6ec(scene);
    SetStateFlagBits_020bc688(0, 5);
    g_menuScene_020c2520 = NULL;
}
