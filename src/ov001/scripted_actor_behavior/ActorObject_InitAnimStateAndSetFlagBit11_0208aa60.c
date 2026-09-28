#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0x894];
    u8 animState[0x660];
    u32 flags;
} Actor;

extern void func_ov001_02089060(void *animState);

void ActorObject_InitAnimStateAndSetFlagBit11_0208aa60(Actor *actor)
{
    func_ov001_02089060(actor->animState);
    actor->flags = actor->flags | 0x800;
}
