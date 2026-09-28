#include "nitro/types.h"

extern void func_02009a98(int cmd, int a);
extern u32 data_02fffc00;
extern u32 data_02fffae0;

u32 func_02009b7c(void) {
    u32 mask;
    u32 value;

    if (!(data_02fffc00 & 0x20000000)) {
        return 0x20;
    }
    func_02009a98(0xd6, 0);
    mask = 0xf8ffffff;
    value = (data_02fffae0 & mask) | 0xa7000000;
    *(vu32 *)0x040001a4 = (mask << 13) & value;
    while (!(*(vu32 *)0x040001a4 & 0x800000)) {
    }
    return *(vu32 *)0x04100010;
}
