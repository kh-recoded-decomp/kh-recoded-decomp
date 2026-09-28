#include "nitro/types.h"

extern u32 func_ov001_0209c26c();
extern u32 func_ov001_020911b4();
extern u32 func_ov021_020b02b8();
extern u32 func_ov021_020b0374();
extern u32 func_ov021_020b4aa4();

u32 func_ov021_020b2860(u32 self, int args)
{
    s32 resolvedA;
    s32 resolvedB;
    s32 resolvedC;
    u32 factor;
    u32 value;

    resolvedA = func_ov021_020b0374();
    resolvedB = func_ov021_020b0374(self, args + 8);
    resolvedC = func_ov021_020b0374(self, args + 0x10);
    resolvedA = func_ov021_020b02b8(self, *(u32 *)(resolvedA + 4));
    resolvedB = func_ov021_020b02b8(self, *(u32 *)(resolvedB + 4));
    if (resolvedA == 0) {
        return 0;
    }
    if (resolvedB == 0) {
        return 0;
    }
    factor = func_ov001_0209c26c();
    value = func_ov021_020b4aa4(self, *(u32 *)(resolvedC + 4));
    func_ov001_020911b4(resolvedA, factor, value, 0);
    return 0;
}
