#include "nitro/types.h"

/* Four zero registers feed each 16-byte FIFO write. */
register u32 sZero0 __asm("r1");
register u32 sZero1 __asm("r2");
register u32 sZero2 __asm("r3");
register u32 sZero3 __asm("r12");

static inline __attribute__((always_inline)) void SendNop(u32 *fifo)
{
    fifo[0] = sZero0;
    fifo[1] = sZero1;
    fifo[2] = sZero2;
    fifo[3] = sZero3;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
}

static inline __attribute__((always_inline)) void SendEightNops(u32 *fifo)
{
    SendNop(fifo);
    SendNop(fifo);
    SendNop(fifo);
    SendNop(fifo);
    SendNop(fifo);
    SendNop(fifo);
    SendNop(fifo);
    SendNop(fifo);
}

void GXi_NopClearFifo128_(void *fifo)
{
    sZero0 = 0;
    sZero1 = 0;
    sZero2 = 0;
    sZero3 = 0;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    SendEightNops(fifo);
    SendEightNops(fifo);
    SendEightNops(fifo);
    SendEightNops(fifo);
}
