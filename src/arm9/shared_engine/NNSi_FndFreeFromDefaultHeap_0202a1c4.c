#include "nitro/types.h"

extern int data_02060394;
extern void FND_FreeExpandedHeapBlock_020132c4(void *heap, void *block);

void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block)
{
    void *heap = *(void **)((char *)&data_02060394 + 4);
    FND_FreeExpandedHeapBlock_020132c4(*(void **)heap, block);
}
