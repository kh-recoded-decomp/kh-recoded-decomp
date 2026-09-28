#include "nitro/types.h"

typedef struct ChannelContext {
    u8 pad_000[0x1dc];
    u16 active;
} ChannelContext;

extern ChannelContext *g_channelContext_020a04f4;
extern int func_ov001_0208b780(void);

void ActorChannel_UpdateIfActive_0208bd1c(void)
{
    if (g_channelContext_020a04f4->active != 0) {
        func_ov001_0208b780();
    }
}
