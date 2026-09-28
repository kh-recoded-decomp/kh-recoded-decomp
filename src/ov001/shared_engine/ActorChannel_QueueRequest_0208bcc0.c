#include "nitro/types.h"

extern u8 *g_channelContext_020a04f4;

void ActorChannel_QueueRequest_0208bcc0(u32 param1, u32 param2)
{
    u8 *ctx = g_channelContext_020a04f4;
    *(u32 *)(g_channelContext_020a04f4 + 0x8c) = *(u32 *)(g_channelContext_020a04f4 + 0x84);
    *(u32 *)(ctx + 0x84) = param2;
    *(u32 *)(ctx + 0x90) = param1;
    *(u32 *)(ctx + 0x94) = *(u32 *)(ctx + 0x90);
    *(u32 *)(ctx + 0x98) = 7;
}
