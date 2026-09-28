#include "nitro/types.h"

extern int func_ov001_0206a814();
extern void func_ov001_02063130();
extern void func_ov001_0206430c();

u32 func_ov040_020bd5c0(void)
{
    int ready;

    ready = func_ov001_0206a814();
    if (ready != 0) {
        func_ov001_02063130(0xfffffffd, 3);
        func_ov001_0206430c();
        return 5;
    }
    return 0xffffffff;
}
