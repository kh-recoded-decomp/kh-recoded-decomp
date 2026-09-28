#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xEF4];
    u32 flags;
} Actor;

void func_ov001_02088b48(Actor *actor)
{
    actor->flags = actor->flags & 0xffffffbf;
}
