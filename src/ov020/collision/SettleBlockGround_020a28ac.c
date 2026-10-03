#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Block {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0x10];
    u16 flags;
    u8 pad_56[6];
    fx32 groundY;
} Block;

extern Block *FindLivePrevBlock_020a27f4(Block *block);
extern Block *FindLiveNextBlock_020a283c(Block *block);

void SettleBlockGround_020a28ac(Block *block)
{
    Block *support = FindLiveNextBlock_020a283c(block);
    Block *above;

    block->flags |= 2;
    if (support->flags & 2) {
        block->groundY = support->groundY + 0x1800;
    } else {
        block->groundY = support->position.y;
    }
    above = FindLivePrevBlock_020a27f4(block);
    if (above != NULL) {
        SettleBlockGround_020a28ac(above);
    }
}
