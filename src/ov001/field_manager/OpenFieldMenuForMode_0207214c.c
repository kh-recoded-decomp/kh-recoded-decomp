#include "nitro/types.h"

typedef struct Scene {
    u8 pad_000[0x480];
    u32 unk0 : 7;
    u32 lockedMode : 1;
    u32 unk8 : 2;
    u32 eventMode : 1;
    u32 unk11 : 21;
} Scene;

typedef struct SceneGlobals {
    int allocEnabled;
    Scene *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04a4;
extern void func_ov001_0207b3e4(u32 menuId, u32 option);
extern void func_ov001_0207b408(u32 menuId, u32 option);

void OpenFieldMenuForMode_0207214c(u32 menuId, u32 option)
{
    Scene *scene = data_ov001_020a04a4.scene;

    if (scene->lockedMode == 1 || scene->eventMode == 1) {
        func_ov001_0207b408(menuId, option);
        return;
    }
    func_ov001_0207b3e4(menuId, option);
}
