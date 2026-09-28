#include "nitro/types.h"

void SetActorCallbackPair_020958d0(u8 *actor, u32 callback, u32 userData)
{
    *(u32 *)(actor + 0x1c0) = callback;
    *(u32 *)(actor + 0x1c4) = userData;
}
