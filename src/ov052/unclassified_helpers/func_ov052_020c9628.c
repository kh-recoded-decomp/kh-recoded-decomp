#include "nitro/types.h"

typedef struct Entity {
    u8 pad_000[0x9AC];
    u64 stateFlags;
} Entity;

BOOL func_ov052_020c9628(Entity *entity, int eventId)
{
    BOOL accepted = FALSE;

    if (eventId != 10 && eventId != 14 && eventId != 27 && (entity->stateFlags & 0x4000000) == 0) {
        accepted = TRUE;
    }
    entity->stateFlags &= ~(u64)0x4000000;
    return accepted;
}
