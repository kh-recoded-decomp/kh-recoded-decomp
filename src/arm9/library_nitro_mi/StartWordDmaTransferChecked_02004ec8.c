#include "nitro/types.h"

extern void MIi_CheckDma0SourceAddress_02005390(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void func_01ff85b4(u32 dmaNo, u32 arg2, u32 arg3, u32 ctrl, u32 arg5);

void StartWordDmaTransferChecked_02004ec8(int dmaNo, u32 arg2, u32 arg3, u32 size, int mode)
{
    volatile u32 *ctrl;
    u32 cntValue;

    if (size == 0) {
        return;
    }

    MIi_CheckDma0SourceAddress_02005390(dmaNo, arg2, size, 0);

    ctrl = (volatile u32 *)0x040000b0 + (dmaNo * 3 + 2);

    while ((*ctrl & 0x80000000) != 0) {
    }

    if (mode != 0) {
        cntValue = (size >> 2) | 0x84000000;
        func_01ff85b4(dmaNo, arg2, arg3, cntValue, 2);
    } else {
        cntValue = (size >> 2) | 0x04000000;
        func_01ff85b4(dmaNo, arg2, arg3, cntValue, 6);
    }

    while ((*ctrl & 0x80000000) != 0) {
    }
}
