#include "nitro/types.h"

typedef void (*PMCallback)(u32 result, void *arg);

extern u32 PMi_SendPxiCommandArray_02010300(u32 *words, int count, u32 reserved, PMCallback callback, void *arg);
extern void func_020049b4(int param1);
extern void AssignIfNotNull_020101fc(u32 value, u32 *out);

void PMi_SendPxiCommandArraySync_02010350(u32 *words, int count)
{
    volatile s32 result;
    u32 sendResult;

    while (TRUE) {
        result = -0x10000;
        sendResult = PMi_SendPxiCommandArray_02010300(words, count, 0, (PMCallback)AssignIfNotNull_020101fc, &result);

        while (sendResult != 0) {
            func_020049b4(0x51d23);
            sendResult = PMi_SendPxiCommandArray_02010300(words, count, 0, (PMCallback)AssignIfNotNull_020101fc, &result);
        }

        while (result == -0x10000) {
            func_020049b4(0x51d23);
        }

        if (result == 0) {
            break;
        }

        func_020049b4(0x51d23);
    }
}
