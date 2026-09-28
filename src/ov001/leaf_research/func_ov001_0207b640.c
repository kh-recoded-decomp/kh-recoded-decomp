#include "nitro/types.h"

extern s32 func_ov001_0207b3cc(void);
extern s32 func_ov001_0207b5e8(void);
extern void func_ov025_020b628c(u32 value);
extern void func_ov025_020b62c4(void);

void func_ov001_0207b640(u32 value)
{
    if (func_ov001_0207b3cc() == 2 && func_ov001_0207b5e8() != 0) {
        func_ov025_020b62c4();
        func_ov025_020b628c(value);
    }
}
