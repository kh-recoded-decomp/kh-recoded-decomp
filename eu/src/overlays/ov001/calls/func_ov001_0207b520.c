#include "nitro/types.h"

extern u32 func_ov001_020645c8(u32 id);
extern void func_ov001_020645dc(u32 id);
extern u32 func_ov001_02064784(void);
extern u32 func_ov001_0207b3f4(void);
extern u32 func_ov001_0207b610(void);
extern void func_ov025_020b6184(void);

extern u32 data_ov001_020a04e8;

void func_ov001_0207b520(void)
{
    s32 panel;
    u32 fault;

    panel = data_ov001_020a04e8;
    fault = func_ov001_02064784();
    if ((fault == 0) && (fault = func_ov001_020645c8(0x3709), fault == 0)) {
        func_ov001_020645dc(0x3709);
    }
    fault = func_ov001_0207b3f4();
    if (fault == 2) {
        fault = func_ov001_0207b610();
        if (fault != 0) {
            func_ov025_020b6184();
        }
        *(u16 *)(panel + 0x100) = 2;
        return;
    }
    *(u16 *)(panel + 0x100) = 1;
}
