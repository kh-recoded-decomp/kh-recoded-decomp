#include "nitro/types.h"

typedef void (*OSIrqFunction)(void *arg);

extern void OS_DisableIrqMask(u32 mask);

typedef struct {
    OSIrqFunction pfnHandler;
    volatile u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern OSiIrqSlot data_02056ae8[];

extern u16 data_02055bc0[];

extern u32 data_027e0000;

#define DTCM ((char *)&data_027e0000)
#define OSi_IrqCheckFlags (*(volatile u32 *)(DTCM + 0x3ff8))

void OSi_IrqCallback_02001c70(u32 slot)
{
    u32 mask = 1 << data_02055bc0[slot];
    OSIrqFunction handler = data_02056ae8[slot].pfnHandler;

    data_02056ae8[slot].pfnHandler = 0;
    if (handler != 0) {
        handler(data_02056ae8[slot].pArg);
    }

    {
        u32 flags = OSi_IrqCheckFlags | mask;
        u32 keep = data_02056ae8[slot].bKeepEnabled;

        OSi_IrqCheckFlags = flags;

        if (keep == 0) {
            OS_DisableIrqMask(mask);
        }
    }
}
