#include "nitro/types.h"

extern int data_02060394;
extern void *AllocateFromExpandedHeapEx_02013134(void *heap, u32 size, int align);

void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size)
{
    void *heap = *(void **)((char *)&data_02060394 + 4);
    return AllocateFromExpandedHeapEx_02013134(*(void **)heap, size, 4);
}
