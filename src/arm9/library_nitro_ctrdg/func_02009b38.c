#include "nitro/types.h"

extern void func_02009a98(int cmd, int a, int b, int c);
extern u32 data_02fffae0;

u32 func_02009b38(int param1, int param2, int param3, int param4) {
    u32 mask = 0xf8ffffff;
    u32 value;

    func_02009a98(0xb8, 0, param3, param4);
    value = (data_02fffae0 & mask) | 0xa7000000;
    *(vu32 *)0x040001a4 = (mask << 13) & value;
    while ((*(vu32 *)0x040001a4 & 0x800000) == 0) {
    }
    return *(vu32 *)0x04100010;
}
