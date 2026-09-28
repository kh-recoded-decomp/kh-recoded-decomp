#include "nitro/types.h"

extern void MIi_CheckDma0SourceAddress_02005390(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void func_01ff85b4(u32 dmaNo, u32 src, u32 dest, u32 ctrl, u32 arg5);

void StartHalfwordDmaTransferChecked_02004f6c(int dmaNo, u32 src, u32 dest, u32 size, int mode)
{
    volatile u32 *ctrl;

    if (size == 0) {
        return;
    }

    MIi_CheckDma0SourceAddress_02005390(dmaNo, src, size, 0);

    ctrl = (volatile u32 *)0x040000b0 + (dmaNo * 3 + 2);

    while ((*ctrl & 0x80000000) != 0) {
    }

    if (mode != 0) {
        func_01ff85b4(dmaNo, src, dest, (size >> 1) | 0x80000000, 2);
    } else {
        func_01ff85b4(dmaNo, src, dest, size >> 1, 6);
    }

    while ((*ctrl & 0x80000000) != 0) {
    }
}
