#include "nitro/types.h"

extern void func_02009a98(int cmd, int a, int b, int c);
extern u32 data_02fffae0;

void func_02009b0c(int device, int unused, int offset, int length) {
    func_02009a98(0xb7, device, offset, length);
    *(vu32 *)0x040001a4 = (data_02fffae0 & 0xf8ffffff) | 0xa1000000;
}
