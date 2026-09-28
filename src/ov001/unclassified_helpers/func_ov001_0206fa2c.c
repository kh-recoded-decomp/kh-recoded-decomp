#include "nitro/types.h"

extern void func_020014f0(u32 context);
extern s32 func_ov001_0207169c(void);
extern void func_ov027_020ba294(u32 context);

void func_ov001_0206fa2c(u32 context)
{
    s32 count;
    s32 index;

    func_ov027_020ba294(context + 0x2d8);
    func_ov027_020ba294(context + 0x2cc);
    func_020014f0(context + 0x1fc);
    count = func_ov001_0207169c();
    index = 0;
    if (0 < count + 1) {
        do {
            func_020014f0(context + 0x230 + index * 0x34);
            index = index + 1;
        } while (index < count + 1);
    }
}
