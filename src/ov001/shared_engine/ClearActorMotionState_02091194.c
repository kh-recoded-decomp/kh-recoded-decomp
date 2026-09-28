#include "nitro/types.h"

void ClearActorMotionState_02091194(u8 *actor)
{
    *(u32 *)(actor + 0x29c) = 0;
    *(u32 *)(actor + 0x2a0) = 0;
    *(u32 *)(actor + 0x2a4) = 0;
}
