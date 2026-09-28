#include "nitro/types.h"

extern int data_02060394;

void *NNSi_FndGetAllocatorForDefaultHeap_0202a268(void *heap)
{
    if (heap == 0) {
        heap = *(void **)((char *)&data_02060394 + 4);
    }
    return (char *)heap + 4;
}
