#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xEF4];
    u32 flags;
} Actor;

BOOL func_ov001_0208a334(Actor *actor)
{
    if ((actor->flags & 8) != 0) {
        return TRUE;
    }
    return FALSE;
}
