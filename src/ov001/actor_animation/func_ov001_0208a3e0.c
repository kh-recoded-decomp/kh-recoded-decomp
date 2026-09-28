#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[4];
    u8 clearRegion[0xc];
    u8 pad_010[0xEE4];
    u32 flags;
} Actor;

extern void func_01ff8830(void *dst, int val, u32 size);

void func_ov001_0208a3e0(Actor *actor)
{
    actor->flags = actor->flags & 0xfffffe7f;
    func_01ff8830(actor->clearRegion, 0, 0xc);
}
