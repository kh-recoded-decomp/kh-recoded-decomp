#include "nitro/types.h"

extern int data_02060394;
extern void *AllocateFromExpandedHeapEx_02013134(void *heap, u32 size, int align);

void *NNSi_FndAllocFromExpHeapEx_0202a1e4(u32 size, void **heap)
{
    if (heap == 0) {
        heap = *(void ***)((char *)&data_02060394 + 4);
    }
    return AllocateFromExpandedHeapEx_02013134(*heap, size, 4);
}
