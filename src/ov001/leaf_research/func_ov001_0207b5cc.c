#include "nitro/types.h"

extern u32 func_ov001_0207b3cc(void);
extern void func_ov025_020b6194(void);

void func_ov001_0207b5cc(void)
{
    u32 fault;

    fault = func_ov001_0207b3cc();
    if (fault == 2) {
        func_ov025_020b6194();
    }
}
