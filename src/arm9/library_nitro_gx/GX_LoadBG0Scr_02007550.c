#include "nitro/types.h"

extern void *G2_GetBG0ScrPtr_02006de0(void);
extern s32 data_02055c1c;
extern void func_02004f6c(s32 dmaNo, const void *src, void *dst, u32 size, s32 width);
extern void func_01ff869c(const void *src, void *dst, u32 size);

void GX_LoadBG0Scr_02007550(const void *src, u32 offset, u32 size)
{
    u8 *base = (u8 *)G2_GetBG0ScrPtr_02006de0();

    if (data_02055c1c != -1 && size > 0x1c) {
        func_02004f6c(data_02055c1c, src, base + offset, size, 1);
        return;
    }
    func_01ff869c(src, base + offset, size);
}
