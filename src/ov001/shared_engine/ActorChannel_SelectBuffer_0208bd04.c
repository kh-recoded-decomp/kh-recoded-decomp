#include "nitro/types.h"

extern u8 *g_channelContext_020a04f4;

void *ActorChannel_SelectBuffer_0208bd04(void)
{
    u8 *result = g_channelContext_020a04f4;
    if (*(s32 *)(g_channelContext_020a04f4 + 0x1ec) != 0) {
        result = g_channelContext_020a04f4 + 0xa0;
    }
    return result;
}
