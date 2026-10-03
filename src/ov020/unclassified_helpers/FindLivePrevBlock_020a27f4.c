#include "nitro/types.h"

typedef struct Block {
    u8 pad_00[4];
    void *pool;
    u8 pad_08[0x4c];
    u16 flags;
    s16 prevIndex;
    s16 nextIndex;
} Block;

extern Block *func_ov001_0208635c(void *pool, int index);

static inline Block *GetPrevBlock(Block *block)
{
    return func_ov001_0208635c(block->pool, block->prevIndex);
}

Block *FindLivePrevBlock_020a27f4(Block *block)
{
    while (block->prevIndex >= 0) {
        block = GetPrevBlock(block);
        if (!(block->flags & 0x8000)) {
            return block;
        }
    }
    return NULL;
}
