#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 func_ov052_020d067c(void *actor, int slot);

VecFx32 GetSlot3WorldPosition_020cbfdc(void *actor)
{
    return func_ov052_020d067c(actor, 3);
}
