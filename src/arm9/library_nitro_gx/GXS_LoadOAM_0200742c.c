#include "nitro/types.h"

extern s32 data_02055c1c;
extern void func_02004ec8(s32 dmaNo, const void *src, void *dst, u32 size, s32 width);
extern void func_01ff8710(const void *src, void *dst, u32 size);

void GXS_LoadOAM_0200742c(const void *src, u32 offset, u32 size)
{
    if (data_02055c1c != -1 && size > 0x30) {
        func_02004ec8(data_02055c1c, src, (void *)(offset + 0x7000400), size, 1);
        return;
    }
    func_01ff8710(src, (void *)(offset + 0x7000400), size);
}
