#include "nitro/types.h"

extern void *G2_GetBG1CharPtr_020070cc(void);
extern s32 data_02055c1c;
extern void func_02004ec8(s32 dmaNo, const void *src, void *dst, u32 size, s32 width);
extern void func_01ff8710(const void *src, void *dst, u32 size);

void GX_LoadBG1Char_020079b0(const void *src, u32 offset, u32 size)
{
    u8 *base = (u8 *)G2_GetBG1CharPtr_020070cc();

    if (data_02055c1c != -1 && size > 0x30) {
        func_02004ec8(data_02055c1c, src, base + offset, size, 1);
        return;
    }
    func_01ff8710(src, base + offset, size);
}
