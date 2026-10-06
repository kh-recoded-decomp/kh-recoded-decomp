#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern s32 IsScreenModeIdle(void);

u32 func_ov028_020bad1c(void)
{
    s32 ready = IsScreenModeIdle();

    if (ready != 0) {
        *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) | 0x8000;
        return 0x11;
    }
    return 0xffffffff;
}
