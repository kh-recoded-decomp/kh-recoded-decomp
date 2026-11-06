#include "nitro/types.h"

extern u32 gOv028FieldSceneWorkStorage;
extern s32 IsScreenModeIdle(void);

u32 Ov028SceneState_WaitFadeOut(void)
{
    s32 ready = IsScreenModeIdle();

    if (ready != 0) {
        *(u16 *)(gOv028FieldSceneWorkStorage + 6) = *(u16 *)(gOv028FieldSceneWorkStorage + 6) | 0x8000;
        return 0x11;
    }
    return 0xffffffff;
}
