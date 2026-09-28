#include "nitro/types.h"

extern s32 data_02055c1c;
extern void func_02004f6c(s32 dmaNo, const void *src, void *dst, u32 size, s32 width);
extern void func_01ff869c(const void *src, void *dst, u32 size);

void GXS_LoadOBJPltt_0200736c(const void *src, u32 offset, u32 size)
{
    if (data_02055c1c != -1 && size > 0x1c) {
        func_02004f6c(data_02055c1c, src, (void *)(offset + 0x5000600), size, 1);
        return;
    }
    func_01ff869c(src, (void *)(offset + 0x5000600), size);
}
