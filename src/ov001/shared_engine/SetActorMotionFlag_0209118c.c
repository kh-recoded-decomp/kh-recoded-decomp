#include "nitro/types.h"

void SetActorMotionFlag_0209118c(u8 *actor, u32 flag)
{
    *(u32 *)(actor + 0x2a4) = flag;
}
