#include "nitro/types.h"

typedef struct HeapBlock {
    struct HeapBlock *next;
} HeapBlock;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeBlockChain_020a2e84(HeapBlock **head)
{
    HeapBlock *block = *head;
    while (block != NULL) {
        HeapBlock *current = block;
        block = block->next;
        NNSi_FndFreeFromDefaultHeap_0202a1c4(current);
    }
    *head = NULL;
}
