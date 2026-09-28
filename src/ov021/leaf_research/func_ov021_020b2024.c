#include "nitro/types.h"

extern u32 func_ov021_020b0374();
extern u32 func_ov021_020b4aa4();

u32 func_ov021_020b2024(u32 self, int args)
{
    s32 resolved;

    resolved = func_ov021_020b0374();
    func_ov021_020b0374(self, args + 8);
    func_ov021_020b0374(self, args + 0x10);
    func_ov021_020b4aa4(self, *(u32 *)(resolved + 4));
    return 0;
}
