#include "nitro/types.h"

extern void func_01ff85b4(u32 dmaNo, u32 src, u32 dest, u32 ctrl, u32 arg5);

void StartWordDmaTransfer_02004e44(int dmaNo, u32 dest, u32 src, u32 size, int mode)
{
    volatile u32 *ctrl;
    u32 cntValue;

    if (size == 0) {
        return;
    }

    ctrl = (volatile u32 *)0x040000b0 + (dmaNo * 3 + 2);

    while ((*ctrl & 0x80000000) != 0) {
    }

    if (mode != 0) {
        cntValue = (size >> 2) | 0x85000000;
        func_01ff85b4(dmaNo, src, dest, cntValue, 0x12);
    } else {
        cntValue = (size >> 2) | 0x05000000;
        func_01ff85b4(dmaNo, src, dest, cntValue, 0x16);
    }

    while ((*ctrl & 0x80000000) != 0) {
    }
}
