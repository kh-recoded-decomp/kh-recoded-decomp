#include "nitro/types.h"

typedef struct PxiSystemWork {
    u8 pad_000[0x388];
    u32 callbackMask[2];
} PxiSystemWork;

BOOL PXI_IsCallbackReady_0200e2e8(u32 fifoTag, int proc)
{
    PxiSystemWork *work = (PxiSystemWork *)0x02fffc00;
    return (work->callbackMask[proc] & (1 << fifoTag)) != 0;
}
