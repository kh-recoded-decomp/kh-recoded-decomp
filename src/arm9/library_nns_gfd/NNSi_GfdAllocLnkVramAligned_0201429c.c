#include "nitro/types.h"

typedef struct LnkVramBlock LnkVramBlock;
struct LnkVramBlock {
    u32 addr;
    u32 szByte;
    LnkVramBlock *pBlkPrev;
    LnkVramBlock *pBlkNext;
};

static inline LnkVramBlock *GetNewBlock(LnkVramBlock **blockPool)
{
    LnkVramBlock *block = *blockPool;

    if (block != NULL) {
        *blockPool = block->pBlkNext;
    }
    return block;
}

static inline void InitBlock(LnkVramBlock *block, u32 addr, u32 szByte)
{
    block->addr = addr;
    block->szByte = szByte;
    block->pBlkPrev = NULL;
    block->pBlkNext = NULL;
}

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

BOOL NNSi_GfdAllocLnkVramAligned_0201429c(LnkVramBlock **freeList, LnkVramBlock **blockPool, u32 *outAddr,
                                          u32 szByte, u32 alignment)
{
    u32 alignedAddr;
    u32 szNeeded;
    u32 difference;
    LnkVramBlock *found = NULL;
    LnkVramBlock *block = *freeList;

    while (block != NULL) {
        if (alignment > 1) {
            alignedAddr = (block->addr + (alignment - 1)) & ~(alignment - 1);
            difference = alignedAddr - block->addr;
            szNeeded = szByte + difference;
        } else {
            alignedAddr = block->addr;
            difference = 0;
            szNeeded = szByte;
        }

        if (block->szByte >= szNeeded) {
            found = block;
            break;
        }
        block = block->pBlkNext;
    }

    if (found != NULL) {
        if (difference > 0) {
            LnkVramBlock *newBlock = GetNewBlock(blockPool);
            if (newBlock != NULL) {
                InitBlock(newBlock, found->addr, difference);
                InsertBlock(freeList, newBlock);
            } else {
                goto failed;
            }
        }

        found->szByte -= szNeeded;
        found->addr += szNeeded;

        if (found->szByte == 0) {
            RemoveBlock(freeList, found);
            InsertBlock(blockPool, found);
        }

        *outAddr = alignedAddr;
        return TRUE;
    }

failed:
    *outAddr = 0;
    return FALSE;
}
