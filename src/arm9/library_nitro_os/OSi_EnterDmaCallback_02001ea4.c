#include "nitro/types.h"

typedef void (*OSIrqFunction)(void *arg);

typedef struct {
    OSIrqFunction pfnHandler;
    u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern OSiIrqSlot data_02056ae8[];
extern u32 OS_EnableIrqMask(u32 mask);

#define OS_IRQ_DMA0_BIT 8

void OSi_EnterDmaCallback_02001ea4(u32 dmaNo, OSIrqFunction function, void *arg)
{
    u32 mask = 1 << (dmaNo + OS_IRQ_DMA0_BIT);

    data_02056ae8[dmaNo].pfnHandler = function;
    data_02056ae8[dmaNo].pArg = arg;
    data_02056ae8[dmaNo].bKeepEnabled = OS_EnableIrqMask(mask) & mask;
}
