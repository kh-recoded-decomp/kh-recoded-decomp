#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *memory);

void FreeDefaultHeapBlockIfSet(void *memory)
{
    if (memory != NULL) {
        NNSi_FndFreeFromDefaultHeap(memory);
    }
}
