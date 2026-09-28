#include "nitro/types.h"

extern u32 data_02055c1c;
extern void func_02004f6c(u32 handle, void *dest, u32 src, u32 size, u32 mode);
extern void func_01ff869c(void *dest, u32 src, u32 size);

void func_02007250(void *dest, u32 srcOffset, u32 size, u32 unused)
{
    if ((data_02055c1c != (u32)-1) && (0x1c < size)) {
        func_02004f6c(data_02055c1c, dest, srcOffset + 0x5000000, size, 1);
        return;
    }
    func_01ff869c(dest, srcOffset + 0x5000000, size);
}
