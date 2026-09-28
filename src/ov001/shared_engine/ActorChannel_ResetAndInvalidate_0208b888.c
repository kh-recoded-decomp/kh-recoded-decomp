#include "nitro/types.h"

extern u8 *g_channelContext_020a04f4;
extern void ActorChannel_ResetFields_0208ae3c(void);

void ActorChannel_ResetAndInvalidate_0208b888(void)
{
    ActorChannel_ResetFields_0208ae3c();
    *(u32 *)(g_channelContext_020a04f4 + 0x1e0) = 0xffffffff;
}
