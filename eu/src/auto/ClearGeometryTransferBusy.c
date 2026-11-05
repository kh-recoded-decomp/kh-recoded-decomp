#include "nitro/types.h"

/* DMA completion callback: the argument is the busy word supplied by the sender. */
void ClearGeometryTransferBusy(void *busyWord)
{
    *(u32 *)busyWord = 0;
}
