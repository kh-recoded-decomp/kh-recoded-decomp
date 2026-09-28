#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x94];
    u8 node[0x104];
    u32 active;
} Owner;

extern void func_0202eee8(void *node);

void ForceReleaseEmbedded_02062598(Owner *owner)
{
    owner->active = 0;
    func_0202eee8(owner->node);
}
