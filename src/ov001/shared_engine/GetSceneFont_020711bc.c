#include "nitro/types.h"

typedef struct SceneGlobals {
    u32 unk_00;
    u8 *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04a4;

void *GetSceneFont_020711bc(void)
{
    return data_ov001_020a04a4.scene + 0x78;
}
