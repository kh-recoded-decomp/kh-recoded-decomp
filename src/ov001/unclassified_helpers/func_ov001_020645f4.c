#include "nitro/types.h"

extern u32 func_ov001_0206459c();

void func_ov001_020645f4(u32 values, u32 extra) {
    s32 index = 0;
    do {
        func_ov001_0206459c(index * 0x20 + 0x3537, 0x20, *(u32 *)(values + index * 4));
        index = index + 1;
    } while (index < 3);
    func_ov001_0206459c(0x3597, 0x10, extra);
}
