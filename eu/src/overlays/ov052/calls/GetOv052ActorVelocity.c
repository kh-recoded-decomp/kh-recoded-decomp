#include "nitro/fx_types.h"

/* Borrowed velocity in the overlay052 actor; distinct from the overlay017 API. */
VecFx32 *GetOv052ActorVelocity(void *actor)
{
    return (VecFx32 *)((u8 *)actor + 0x9c8);
}
