#include "nitro/types.h"

extern u8 *g_channelContext_020a04f4;
extern void func_0203a970(void *channel);

void ActorChannel_Destroy_0208b760(void)
{
    func_0203a970(g_channelContext_020a04f4 + 0x140);
    g_channelContext_020a04f4 = 0;
}
