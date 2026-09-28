#include "nitro/types.h"

extern struct {
    u8 pad_00[0xc];
    u32 sBGExtPlttLCDCOffset;
    u32 sBGExtPlttLCDCBlk;
} data_02056f0c;

extern s32 data_02055c1c;
extern void func_0200511c(s32 dmaNo, const void *src, void *dst, u32 size, s32 arg5, s32 arg6, s32 mode);
extern void func_01ff8710(const void *src, void *dst, u32 size);

void GX_LoadBGExtPltt_02007cdc(const void *src, u32 offset, u32 size)
{
    void *dst = (void *)(data_02056f0c.sBGExtPlttLCDCBlk + offset - data_02056f0c.sBGExtPlttLCDCOffset);

    if (data_02055c1c != -1) {
        func_0200511c(data_02055c1c, src, dst, size, 0, 0, 1);
        return;
    }
    func_01ff8710(src, dst, size);
}
