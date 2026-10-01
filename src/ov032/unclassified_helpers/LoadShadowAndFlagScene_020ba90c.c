#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 mode;
} SceneState;

typedef struct {
    u8 *context;
    SceneState *scene;
} Ov032Globals;

extern Ov032Globals data_ov032_020c0060;
extern s32 func_ov001_02063404(void);
extern void ObjectManager_LoadShadowModel_0207efac(void);

s32 LoadShadowAndFlagScene_020ba90c(void) {
    if (func_ov001_02063404() == 1 && data_ov032_020c0060.scene->mode != 3) {
        data_ov032_020c0060.scene->mode = 0;
    }
    ObjectManager_LoadShadowModel_0207efac();
    data_ov032_020c0060.scene->flags |= 0x8000;
    return 2;
}
