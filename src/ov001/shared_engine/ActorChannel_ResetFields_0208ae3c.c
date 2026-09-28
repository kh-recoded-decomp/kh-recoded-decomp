#include "nitro/types.h"

extern u8 *g_channelContext_020a04f4;
extern void func_0203a970(void *channel);

void ActorChannel_ResetFields_0208ae3c(void)
{
    u8 *ctx = g_channelContext_020a04f4;
    func_0203a970(ctx + 0x140);
    *(s32 *)(ctx + 0x1e4) = 0;
    *(s32 *)(ctx + 0x1e8) = 0;
    *(s32 *)(ctx + 0x1ec) = 0;
    *(s32 *)(ctx + 0x98) = 0;
}
