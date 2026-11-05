#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern s32 IsScreenModeIdle(void);

u32 FieldSceneState_EndSlowdownWhenScreenIdle(void)
{
    s32 ready = IsScreenModeIdle();

    if (ready != 0) {
        *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) & 0xffbf;
        return 7;
    }
    return 0xffffffff;
}
