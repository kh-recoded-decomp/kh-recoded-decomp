#include "nitro/types.h"

extern int data_02060394;
extern void *AllocateFromExpandedHeapEx_02013134(void *heap, u32 size, int align);

void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align)
{
    void *heap = *(void **)((char *)&data_02060394 + 4);
    return AllocateFromExpandedHeapEx_02013134(*(void **)heap, size, align);
}
