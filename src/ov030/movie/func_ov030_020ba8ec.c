#include "nitro/types.h"

extern s32 func_ov001_0206a814(void);
extern void func_ov001_02063130(u32 a, u32 b);
extern void func_ov001_0206430c(void);

u32 func_ov030_020ba8ec(void)
{
    s32 ready;

    ready = func_ov001_0206a814();
    if (ready != 0) {
        func_ov001_02063130(0xfffffffd, 3);
        func_ov001_0206430c();
        return 7;
    }
    return 0xffffffff;
}
