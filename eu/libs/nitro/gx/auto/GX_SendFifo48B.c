#include "nitro/types.h"

/* These caller-clobbered bindings apply only to this leaf's file. */
register const u32 *sFifoSource __asm("r0");
register u32 *sFifoDestination __asm("r1");

static __forceinline void SendThreeWords(void)
{
    u32 first = sFifoSource[0];
    u32 second = sFifoSource[1];
    u32 third = sFifoSource[2];
    sFifoSource += 3;

    sFifoDestination[0] = first;
    sFifoDestination[1] = second;
    sFifoDestination[2] = third;
    /* Preserve every group written to the memory-mapped FIFO. */
    __memory_changed();
}

/* Both buffers must be word-aligned; the source contains twelve words. */
void GX_SendFifo48B(void *source, void *destination)
{
    sFifoSource = source;
    sFifoDestination = destination;

    SendThreeWords();
    SendThreeWords();
    SendThreeWords();
    SendThreeWords();
}
