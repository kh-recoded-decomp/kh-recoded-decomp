#include "nitro/types.h"

typedef int GXVRamTex;

extern struct {
    u32 pad0;
    u32 sTexLCDCBlk1;
    u32 sTexPlttLCDCBlk;
    int sTexPltt;
    u32 pad10;
    GXVRamTex sTex;
    u32 sTexLCDCBlk2;
    u32 sSzTexBlk1;
} data_02056f28;

extern s32 data_02055c1c;
extern void StartWordDmaTransferChecked_02004ec8(s32 dmaNo, const void *src, void *dst, u32 size, s32 width);
extern void func_0200511c(s32 dmaNo, const void *src, void *dst, u32 size, s32 arg5, s32 arg6, s32 mode);
extern void func_01ff8710(const void *src, void *dst, u32 size);

void GX_LoadTex_02008050(const void *src, u32 offset, u32 size)
{
    u32 blk2 = data_02056f28.sTexLCDCBlk2;
    void *dst;

    if (blk2 == 0) {
        dst = (void *)(data_02056f28.sTexLCDCBlk1 + offset);
    } else {
        u32 szBlk1 = data_02056f28.sSzTexBlk1;

        if (offset + size < szBlk1) {
            dst = (void *)(data_02056f28.sTexLCDCBlk1 + offset);
        } else if (offset >= szBlk1) {
            dst = (void *)(blk2 + offset - szBlk1);
        } else {
            u32 firstSize = szBlk1 - offset;
            void *firstDst = (void *)(data_02056f28.sTexLCDCBlk1 + offset);

            if (data_02055c1c != -1 && firstSize > 0x30) {
                StartWordDmaTransferChecked_02004ec8(data_02055c1c, src, firstDst, firstSize, 1);
            } else {
                func_01ff8710(src, firstDst, firstSize);
            }
            if (data_02055c1c != -1) {
                func_0200511c(data_02055c1c, (const u8 *)src + firstSize, (void *)blk2, size - firstSize, 0, 0, 1);
                return;
            }
            func_01ff8710((const u8 *)src + firstSize, (void *)blk2, size - firstSize);
            return;
        }
    }

    if (data_02055c1c != -1) {
        func_0200511c(data_02055c1c, src, dst, size, 0, 0, 1);
        return;
    }
    func_01ff8710(src, dst, size);
}
