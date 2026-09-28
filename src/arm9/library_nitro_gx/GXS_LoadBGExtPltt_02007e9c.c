#include "nitro/types.h"

extern s32 data_02055c1c;
extern void func_0200511c(s32 dmaNo, const void *src, void *dst, u32 size, s32 arg5, s32 arg6, s32 mode);
extern void func_01ff8710(const void *src, void *dst, u32 size);

void GXS_LoadBGExtPltt_02007e9c(const void *src, u32 offset, u32 size)
{
    if (data_02055c1c != -1) {
        func_0200511c(data_02055c1c, src, (void *)(offset + 0x6898000), size, 0, 0, 1);
        return;
    }
    func_01ff8710(src, (void *)(offset + 0x6898000), size);
}
