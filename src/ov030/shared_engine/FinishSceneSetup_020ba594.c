#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 mode;
} SceneState;

extern SceneState *data_ov030_020bd000;

extern int func_ov001_02063404(void);
extern void ObjectManager_LoadShadowModel_0207efac(void);

int FinishSceneSetup_020ba594(void) {
    if (func_ov001_02063404() == 1 && data_ov030_020bd000->mode != 3) {
        data_ov030_020bd000->mode = 0;
    }
    ObjectManager_LoadShadowModel_0207efac();
    data_ov030_020bd000->flags |= 0x8000;
    return 2;
}
