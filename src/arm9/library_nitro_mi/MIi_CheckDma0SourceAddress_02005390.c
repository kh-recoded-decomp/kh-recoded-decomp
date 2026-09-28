#include "nitro/types.h"
#include "nitro/mi.h"
#include "nitro/os.h"

static inline void MIi_CallCallback(MIDmaCallback callback, void *arg)
{
    if (callback) {
        (callback)(arg);
    }
}

extern void MIi_CheckDma0SourceAddress_02005390(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 dmaType);
extern void MIi_DmaSetParams(u32 dmaNo, u32 src, u32 dest, u32 ctrl);
extern void func_01ff85d0(u32 dmaNo, u32 src, u32 dest, u32 ctrl);
#define MIi_DmaSetParams_wait func_01ff85d0
extern void MI_WaitDma(u32 dmaNo);
extern void OSi_EnterDmaCallback(u32 dmaNo, MIDmaCallback callback, void *arg);
extern u32 OS_ResetRequestIrqMask(u32 intr);
extern void OS_Terminate(void);

extern MIiGXDmaParams data_020446b0;
#define MIi_GXDmaParams data_020446b0
extern void MIi_DMACallback(void *arg);
extern void MIi_DMAFastCallback(void *arg);

void MIi_CheckDma0SourceAddress_02005390 (u32 dmaNo, u32 src, u32 size, u32 dir)
{
    if (dmaNo == 0) {
        u32 addStart;
        u32 addEnd;

        addStart = src & 0xff000000;

        switch (dir) {
        case MI_DMA_SRC_INC:
            addEnd = src + size;
            break;
        case MI_DMA_SRC_DEC:
            addEnd = src - size;
            break;
        default:
            addEnd = src;
            break;
        }

        addEnd &= 0xff000000;

        if (addStart == 0x04000000 || addStart >= 0x08000000 ||
            addEnd == 0x04000000 || addEnd >= 0x08000000) {
            OS_Panic("illegal DMA0 source address.");
        }
    }
}
