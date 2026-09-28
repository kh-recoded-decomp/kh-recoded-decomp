#include "nitro/types.h"

typedef struct LnkVramBlock LnkVramBlock;
struct LnkVramBlock {
    u32 addr;
    u32 szByte;
    LnkVramBlock *pBlkPrev;
    LnkVramBlock *pBlkNext;
};

typedef struct LnkMemRegion {
    u32 start;
    u32 end;
} LnkMemRegion;

static inline void RemoveBlock(LnkVramBlock **listHead, LnkVramBlock *block)
{
    LnkVramBlock *const prev = block->pBlkPrev;
    LnkVramBlock *const next = block->pBlkNext;

    if (prev != NULL) {
        prev->pBlkNext = next;
    } else {
        *listHead = next;
    }
    if (next != NULL) {
        next->pBlkPrev = prev;
    }
}

static inline void InsertBlock(LnkVramBlock **listHead, LnkVramBlock *block)
{
    if (*listHead != NULL) {
        (*listHead)->pBlkPrev = block;
    }
    block->pBlkNext = *listHead;
    block->pBlkPrev = NULL;
    *listHead = block;
}

BOOL MergeLnkVramRegion_020140f8(LnkVramBlock **freeList, LnkVramBlock **blockPool, LnkMemRegion *region)
{
    LnkVramBlock *cursor = *freeList;
    LnkVramBlock *next = NULL;
    BOOL merged = FALSE;

    while (cursor != NULL) {
        next = cursor->pBlkNext;

        if (cursor->addr == region->end) {
            region->end = cursor->addr + cursor->szByte;
            RemoveBlock(freeList, cursor);
            InsertBlock(blockPool, cursor);
            merged |= TRUE;
        }
        if (cursor->addr + cursor->szByte == region->start) {
            region->start = cursor->addr;
            RemoveBlock(freeList, cursor);
            InsertBlock(blockPool, cursor);
            merged |= TRUE;
        }
        cursor = next;
    }
    return merged;
}
