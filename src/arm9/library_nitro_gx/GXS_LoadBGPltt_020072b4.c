#include "nitro/types.h"

extern s32 data_02055c1c;
extern void StartHalfwordDmaTransferChecked_02004f6c(s32 dmaNo, const void *src, void *dst, u32 size, s32 mode);
extern void MIi_CpuCopy16_01ff869c(const void *src, void *dst, u32 size);

void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size)
{
    if (data_02055c1c != -1 && size > 0x1c) {
        StartHalfwordDmaTransferChecked_02004f6c(data_02055c1c, src, (void *)(offset + 0x400 + 0x5000000), size, 1);
        return;
    }
    MIi_CpuCopy16_01ff869c(src, (void *)(offset + 0x400 + 0x5000000), size);
}
