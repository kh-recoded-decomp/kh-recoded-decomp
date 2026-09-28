#include "nitro/types.h"

typedef void (*PMCallback)(u32 result, void *arg);

extern u32 PMi_SendChannelValueAsync_02010418(u32 channel, u32 value, u32 reserved, PMCallback callback, void *arg);
extern void func_020101a8(void);
extern void AssignIfNotNull_020101fc(u32 value, u32 *out);

u32 PMi_SendChannelValueSync_02010448(u32 channel, u32 value, u32 reserved)
{
    u32 result;
    u32 sendResult = PMi_SendChannelValueAsync_02010418(channel, value, reserved, (PMCallback)AssignIfNotNull_020101fc, &result);

    if (sendResult == 0) {
        func_020101a8();
        sendResult = result;
    }

    return sendResult;
}
