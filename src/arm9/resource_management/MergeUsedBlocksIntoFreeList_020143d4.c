#include "nitro/types.h"

typedef struct Block Block;
struct Block {
    int start;
    int size;
    Block *prev;
    Block *next;
};

typedef struct {
    int start;
    int end;
} Range;

extern int func_020140f8(Block **usedListHead, Block **freeListHead, Range *range);

void MergeUsedBlocksIntoFreeList_020143d4(Block **usedListHead, Block **freeListHead)
{
    Block *block = *usedListHead;
    Range range;

    if (block == NULL) {
        return;
    }
    do {
        range.start = block->start;
        range.end = block->start + block->size;
        if (func_020140f8(usedListHead, freeListHead, &range) == 0) {
            block = block->next;
        } else {
            block->start = range.start;
            block->size = range.end - range.start;
            block = *usedListHead;
        }
    } while (block != NULL);
}
