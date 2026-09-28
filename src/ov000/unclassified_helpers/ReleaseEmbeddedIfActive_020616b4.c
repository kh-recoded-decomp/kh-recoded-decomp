#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x94];
    u8 node[0x104];
    u32 active;
} Owner;

extern void func_0202eee8(void *node);

void ReleaseEmbeddedIfActive_020616b4(Owner *owner)
{
    if (owner->active == 0) {
        return;
    }
    func_0202eee8(owner->node);
    owner->active = 0;
}
