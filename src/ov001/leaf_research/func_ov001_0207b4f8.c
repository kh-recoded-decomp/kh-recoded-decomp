#include "nitro/types.h"

extern u32 func_ov001_020645c8(u32 id);
extern void func_ov001_020645dc(u32 id);
extern u32 func_ov001_02064784(void);
extern u32 func_ov001_0207b3cc(void);
extern u32 func_ov001_0207b5e8(void);
extern void func_ov025_020b6164(void);

extern u32 g_activePanel_020a04c8;

void func_ov001_0207b4f8(void)
{
    s32 panel;
    u32 fault;

    panel = g_activePanel_020a04c8;
    fault = func_ov001_02064784();
    if ((fault == 0) && (fault = func_ov001_020645c8(0x3709), fault == 0)) {
        func_ov001_020645dc(0x3709);
    }
    fault = func_ov001_0207b3cc();
    if (fault == 2) {
        fault = func_ov001_0207b5e8();
        if (fault != 0) {
            func_ov025_020b6164();
        }
        *(u16 *)(panel + 0x100) = 2;
        return;
    }
    *(u16 *)(panel + 0x100) = 1;
}
