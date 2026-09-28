#include "nitro/types.h"

extern u32 PM_ForceToPowerOffAsync_02010534(void (*callback)(u32 value, u32 *out), void *arg);
extern void func_020101a8(void);
extern void AssignIfNotNull_020101fc(u32 value, u32 *out);
extern u32 data_02055c44;

u32 PM_ForceToPowerOffSync_02010550(void)
{
    u32 result;
    u32 sendResult = PM_ForceToPowerOffAsync_02010534(AssignIfNotNull_020101fc, &result);

    if (sendResult == 0) {
        data_02055c44 = 0xc;
        func_020101a8();
        data_02055c44 = 2;
        sendResult = result;
    }

    return sendResult;
}
