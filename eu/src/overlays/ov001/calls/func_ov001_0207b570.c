#include "nitro/types.h"

extern u32 func_ov001_0207b3f4(void);
extern u32 func_ov001_0207b610(void);
extern void func_ov025_020b619c(void);

void func_ov001_0207b570(void)
{
    u32 fault;

    fault = func_ov001_0207b3f4();
    if ((fault == 2) && (fault = func_ov001_0207b610(), fault != 0)) {
        func_ov025_020b619c();
    }
}
