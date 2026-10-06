#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern s32 func_ov001_02063620(void);
extern void PushVramState(void);

u32 func_ov030_020ba588(void)
{
    s32 ready;

    ready = func_ov001_02063620();
    if (ready != 0) {
        return 0xffffffff;
    }
    PushVramState();
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) | 0x8000;
    return 1;
}
