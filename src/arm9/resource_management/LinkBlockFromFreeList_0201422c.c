#include "nitro/types.h"

typedef struct Block Block;
struct Block {
    int start;
    int size;
    Block *prev;
    Block *next;
};

BOOL LinkBlockFromFreeList_0201422c(Block **usedListHead, Block **freeListHead, int start, int size)
{
    Block *block = *freeListHead;

    if (block != NULL) {
        *freeListHead = block->next;
    }

    if (block == NULL) {
        goto fail;
    }

    block->start = start;
    block->size = size;
    block->prev = NULL;
    block->next = NULL;

    if (*usedListHead != NULL) {
        (*usedListHead)->prev = block;
    }

    block->next = *usedListHead;
    block->prev = NULL;
    *usedListHead = block;
    return TRUE;

fail:
    return FALSE;
}
