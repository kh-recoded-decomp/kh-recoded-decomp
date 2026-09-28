#include "nitro/types.h"

typedef struct SceneGlobals {
    u32 unk_00;
    u8 *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04a4;

void *GetSceneTagTracker_020711b0(void)
{
    return data_ov001_020a04a4.scene + 0x1c;
}
