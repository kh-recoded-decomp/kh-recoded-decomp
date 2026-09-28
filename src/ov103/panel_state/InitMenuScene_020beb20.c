#include "nitro/types.h"

typedef struct {
    void *fileData;
    u8 pad_04[0xc];
} GraphicsResource;

typedef struct MenuScene {
    u8 pad_000[0x134];
    GraphicsResource resources[4];
} MenuScene;

extern MenuScene *g_menuScene_020c0700;
extern void SetupMenuDisplay_020bed3c(void);
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);
extern void SetSceneState_020c02f4(int state, MenuScene *scene);

BOOL InitMenuScene_020beb20(MenuScene *scene)
{
    g_menuScene_020c0700 = scene;
    scene->resources[3].fileData = NULL;
    SetupMenuDisplay_020bed3c();
    SetStateFlagBits_020bc688(5, 0);
    SetSceneState_020c02f4(1, scene);
    return TRUE;
}
