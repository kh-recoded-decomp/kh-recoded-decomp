#include "nitro/types.h"

void ClearActorMotionSpeed_020911a8(u8 *actor)
{
    *(u32 *)(actor + 0x294) = 0;
}
