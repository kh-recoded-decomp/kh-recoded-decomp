#include "nitro/types.h"

typedef void (*PMCallback)(u32 result, void *arg);

extern u32 PMi_SendPxiCommandArray_02010300(u32 *words, int count, u32 reserved, PMCallback callback, void *arg);

u32 PMi_SendChannelValueAsync_02010418(u32 channel, u32 value, u32 reserved, PMCallback callback, void *arg)
{
    u32 words[2];

    words[0] = (channel & 0xff) | 0x02006100;
    words[1] = (value & 0xffff) | 0x01010000;

    return PMi_SendPxiCommandArray_02010300(words, 2, reserved, callback, arg);
}
