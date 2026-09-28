#include "nitro/types.h"

typedef void (*PMCallback)(u32 result, void *arg);

extern u32 PMi_SendChannelValueAsync_02010418(u32 channel, u32 value, u32 reserved, PMCallback callback, void *arg);

u32 func_02010468(int selector, PMCallback callback, void *arg)
{
    u32 channel;

    switch (selector) {
    case 1:
        channel = 1;
        break;
    case 3:
        channel = 2;
        break;
    case 2:
        channel = 3;
        break;
    default:
        channel = 0;
        break;
    }

    if (channel != 0) {
        return PMi_SendChannelValueAsync_02010418(channel, 0, 0, callback, arg);
    }
    return 0xffff;
}
