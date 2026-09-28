#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x53];
    s8 linkedCallbackId;
} Actor;

void
SetLinkedCallbackId_020a3580(Actor *self, s8 id)
{
    self->linkedCallbackId = id;
}
