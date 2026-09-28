#include "nitro/types.h"

struct NNSiFndHeapHead;
extern struct NNSiFndHeapHead *CreateExpandedHeap_020130f0(void *startAddress, u32 size, u16 optionFlag);
extern void *PXI_Init_02013128(void *heapStart);
extern void NNS_FndInitAllocatorForExpHeap_02013740(int *allocator, int a, int b);

void func_0202a0f0(int *state)
{
    void *start = (void *)state[0];
    int size = *(int *)((char *)start + 0x1c) - (int)start;
    PXI_Init_02013128(start);
    void *heap = CreateExpandedHeap_020130f0(start, size, 1);
    state[0] = (int)heap;
    NNS_FndInitAllocatorForExpHeap_02013740(state + 1, (int)heap, 4);
}
