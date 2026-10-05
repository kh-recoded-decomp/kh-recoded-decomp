#include "nitro/types.h"

extern void StopOv070BossEffects(void *actor, void *owner);

void StopOv070BossEffectsForOwner(void *actor, void *owner)
{
    if (*(void **)((u8 *)actor + 8) == owner) {
        StopOv070BossEffects(actor, owner);
    }
}
