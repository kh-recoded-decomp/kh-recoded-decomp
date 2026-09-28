#include "nitro/types.h"

extern void MIi_CheckAnotherAutoDMA_02005304(int dmaNo, u32 timing);
extern void MIi_CheckDma0SourceAddress_02005390(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void func_01ff85b4(u32 dmaNo, u32 src, u32 dest, u32 ctrl, u32 arg5);

void MIi_CardDmaCopy32_020056d4(int dmaNo, u32 src, u32 dest, int size)
{
    volatile u32 *ctrl;

    MIi_CheckAnotherAutoDMA_02005304(dmaNo, 0xffffffff);
    MIi_CheckDma0SourceAddress_02005390(dmaNo, src, size, 0x1000000);

    if (size == 0) {
        return;
    }

    ctrl = (volatile u32 *)0x040000b0 + (dmaNo * 3 + 2);

    while ((*ctrl & 0x80000000) != 0) {
    }

    func_01ff85b4(dmaNo, src, dest, 0xaf000001, 0);
}
