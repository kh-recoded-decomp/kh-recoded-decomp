#include "nitro/types.h"

extern u32 func_ov001_0207b3cc(void);
extern u32 func_ov001_0207b5e8(void);
extern void func_ov025_020b617c(void);

void func_ov001_0207b548(void)
{
    u32 fault;

    fault = func_ov001_0207b3cc();
    if ((fault == 2) && (fault = func_ov001_0207b5e8(), fault != 0)) {
        func_ov025_020b617c();
    }
}
