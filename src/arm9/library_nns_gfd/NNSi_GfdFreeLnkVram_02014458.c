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

extern BOOL MergeLnkVramRegion_020140f8(LnkVramBlock **freeList, LnkVramBlock **blockPool, LnkMemRegion *region);

BOOL NNSi_GfdFreeLnkVram_02014458(LnkVramBlock **freeList, LnkVramBlock **blockPool, u32 addr, u32 szByte)
{
    LnkMemRegion region;
    LnkVramBlock *block;

    region.start = addr;
    region.end = addr + szByte;
    MergeLnkVramRegion_020140f8(freeList, blockPool, &region);

    block = *blockPool;
    if (block != NULL) {
        *blockPool = block->pBlkNext;
    }
    if (block == NULL) {
        return FALSE;
    }

    block->addr = region.start;
    block->szByte = region.end - region.start;
    block->pBlkPrev = NULL;
    block->pBlkNext = NULL;

    if (*freeList != NULL) {
        (*freeList)->pBlkPrev = block;
    }
    block->pBlkNext = *freeList;
    block->pBlkPrev = NULL;
    *freeList = block;
    return TRUE;
}
