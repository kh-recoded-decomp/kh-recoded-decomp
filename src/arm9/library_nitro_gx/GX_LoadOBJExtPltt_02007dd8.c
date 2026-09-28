#include "nitro/types.h"

extern struct {
    u32 sSubBGExtPltt;
    u8 *sOBJExtPlttLCDCBlk;
} data_02056f0c;

extern s32 data_02055c1c;
extern void func_0200511c(s32 dmaNo, const void *src, void *dst, u32 size, s32 arg5, s32 arg6, s32 mode);
extern void func_01ff8710(const void *src, void *dst, u32 size);

void GX_LoadOBJExtPltt_02007dd8(const void *src, u32 offset, u32 size)
{
    u8 *base = data_02056f0c.sOBJExtPlttLCDCBlk;

    if (data_02055c1c != -1) {
        func_0200511c(data_02055c1c, src, base + offset, size, 0, 0, 1);
        return;
    }
    func_01ff8710(src, base + offset, size);
}
