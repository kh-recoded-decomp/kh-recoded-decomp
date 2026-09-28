#include "nitro/types.h"

extern u32 data_02055c1c;
extern void func_02004ec8(u32 handle, void *dest, u32 src, u32 size, u32 mode);
extern void func_01ff8710(void *dest, u32 src, u32 size);

void func_020073c8(void *dest, u32 srcOffset, u32 size, u32 unused)
{
    if ((data_02055c1c != (u32)-1) && (0x30 < size)) {
        func_02004ec8(data_02055c1c, dest, srcOffset + 0x7000000, size, 1);
        return;
    }
    func_01ff8710(dest, srcOffset + 0x7000000, size);
}
