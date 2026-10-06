#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern s32 func_ov001_0207b6b0(void);
extern void StoreToGlobalPtr4Field28(u32 value);

u32 func_ov030_020ba774(void)
{
    s32 ready;

    ready = func_ov001_0207b6b0();
    if (ready == 0) {
        return 0xffffffff;
    }
    if ((*(u16 *)(data_ov030_020bd020 + 6) & 1) != 0) {
        *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) & 0xfffe;
    }
    StoreToGlobalPtr4Field28(0);
    return 7;
}
