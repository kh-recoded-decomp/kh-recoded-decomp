#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    void *heapBlock;
} Ov045HeapHolder;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

/* Frees a held heap block and clears it. */
void ReleaseHeapBlockIfAllocated_020c0320(Ov045HeapHolder *holder)
{
    if (holder->heapBlock != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(holder->heapBlock);
        holder->heapBlock = NULL;
    }
}
