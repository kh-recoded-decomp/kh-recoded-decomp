#include "nitro/types.h"

extern void func_02009a98(int cmd, int a, int b, int c);
extern u32 data_02fffae0;

void func_02009c14(int device, int unused, int offset, int length) {
    u32 mask = 0xf8ffffff;
    u32 value;

    func_02009a98(0xb5, 0, offset, length);
    value = (data_02fffae0 & mask) | 0xa0000000;
    *(vu32 *)0x040001a4 = (mask << 13) & value;
    while (*(vu32 *)0x040001a4 & 0x80000000) {
    }
}
