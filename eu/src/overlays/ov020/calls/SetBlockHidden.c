#include "nitro/types.h"

typedef struct Block {
    u8 pad_00[0x30];
    u16 renderFlags;
    u8 entityId;
    u8 pad_33[0x21];
    u16 flags;
} Block;

extern BOOL func_ov020_020a34a4(Block *block);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);

void SetBlockHidden(Block *block, BOOL hidden)
{
    if (hidden) {
        block->flags |= 8;
        block->renderFlags &= ~0x10;
        block->renderFlags &= ~8;
    } else {
        block->flags &= ~8;
        block->renderFlags |= 0x10;
        block->renderFlags |= 8;
    }
    if (block->renderFlags & 4) {
        ActorSlot_SetFlag8ByIndex(block->entityId,
                                           !func_ov020_020a34a4(block) && !(block->flags & 0x8000) ? TRUE : FALSE);
    }
}
