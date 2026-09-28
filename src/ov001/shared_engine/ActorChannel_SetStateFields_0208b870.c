#include "nitro/types.h"

extern u8 *g_channelContext_020a04f4;

void ActorChannel_SetStateFields_0208b870(u32 state, u32 value1e8)
{
    u8 *ctx = g_channelContext_020a04f4;
    *(u32 *)(g_channelContext_020a04f4 + 0x98) = state;
    *(u32 *)(ctx + 0x1e8) = value1e8;
}
