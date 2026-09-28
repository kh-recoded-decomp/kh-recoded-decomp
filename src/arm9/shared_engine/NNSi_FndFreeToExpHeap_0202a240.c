#include "nitro/types.h"

extern int data_02060394;
extern void FND_FreeExpandedHeapBlock_020132c4(void *heap, void *block);

void NNSi_FndFreeToExpHeap_0202a240(void *block, void **heap)
{
    if (heap == 0) {
        heap = *(void ***)((char *)&data_02060394 + 4);
    }
    FND_FreeExpandedHeapBlock_020132c4(*heap, block);
}
