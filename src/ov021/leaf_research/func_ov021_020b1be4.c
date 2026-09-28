#include "nitro/types.h"

extern u32 func_ov001_02091248();
extern u32 func_ov001_02091600();
extern u32 func_ov021_020b02b8();
extern u32 func_ov021_020b0374();
extern u32 TaggedValueToInt_020b0398();
extern u32 func_ov021_020b4aa4();

u32 func_ov021_020b1be4(int self, int args)
{
    s32 resolved;
    u32 value;
    s32 target;

    resolved = func_ov021_020b0374(self, args + 8);
    func_ov021_020b0374(self, args + 0x10);
    value = TaggedValueToInt_020b0398();
    target = func_ov021_020b02b8(self, value);
    if (target == 0) {
        return 0;
    }
    value = func_ov021_020b4aa4(self, *(u32 *)(resolved + 4));
    value = func_ov001_02091248(target, value);
    func_ov001_02091600(target, value, self + 0x34);
    return 0;
}
