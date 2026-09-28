#include "nitro/types.h"

extern u32 func_ov001_020645c8(u32 id);
extern u32 func_ov001_02064784(void);
extern void func_ov001_0207b27c(u32 arg);

extern u32 g_activePanel_020a04c8;

void func_ov001_0207b338(u32 arg)
{
    u32 fault;

    fault = func_ov001_02064784();
    if ((fault == 0) && (fault = func_ov001_020645c8(0x370b), fault != 0)) {
        *(u32 *)(g_activePanel_020a04c8 + 0x108) = 2;
    }
    func_ov001_0207b27c(arg);
}
