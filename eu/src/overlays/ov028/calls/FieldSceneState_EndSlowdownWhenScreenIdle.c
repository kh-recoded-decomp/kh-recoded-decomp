#include "nitro/types.h"

extern u32 gOv028FieldSceneWorkStorage;
extern s32 IsScreenModeIdle(void);

u32 FieldSceneState_EndSlowdownWhenScreenIdle(void)
{
    s32 ready = IsScreenModeIdle();

    if (ready != 0) {
        *(u16 *)(gOv028FieldSceneWorkStorage + 6) = *(u16 *)(gOv028FieldSceneWorkStorage + 6) & 0xffbf;
        return 7;
    }
    return 0xffffffff;
}
