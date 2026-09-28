#include "nitro/types.h"

typedef struct LnkVramBlock LnkVramBlock;
struct LnkVramBlock {
    u32 addr;
    u32 szByte;
    LnkVramBlock *pBlkPrev;
    LnkVramBlock *pBlkNext;
};

LnkVramBlock *NNSi_GfdInitLnkVramBlockPool_020141e8(LnkVramBlock *blocks, u32 blockCount)
{
    u32 i;

    for (i = 0; i < blockCount - 1; i++) {
        blocks[i].pBlkNext = &blocks[i + 1];
        blocks[i + 1].pBlkPrev = &blocks[i];
    }
    blocks[0].pBlkPrev = NULL;
    blocks[blockCount - 1].pBlkNext = NULL;
    return blocks;
}
