#include "nitro/types.h"

extern int func_ov001_02068084(void);
extern void func_ov001_020645dc(u32 flag);
extern void func_ov001_02063a80(int category, int amount);
extern u32 func_ov001_02064574(u32 category, u32 index);
extern void func_ov001_0206459c(u32 category, u32 index, u32 value);

void func_ov001_0206df78(void)
{
    int flagSet;
    u32 count;

    flagSet = func_ov001_02068084();
    if (flagSet == 0) {
        func_ov001_020645dc(0x3707);
    }
    func_ov001_02063a80(6, 1);
    count = func_ov001_02064574(0xb26, 0x11);
    if (count < 99999) {
        func_ov001_0206459c(0xb26, 0x11, count + 1);
    }
}
