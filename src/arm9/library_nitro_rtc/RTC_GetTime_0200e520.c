#include "nitro/types.h"

typedef struct RtcWork {
    u8 pad_00[0x24];
    int lastResult;
} RtcWork;

extern RtcWork data_02057c0c;
extern int RTC_GetTimeAsync_0200e4d4(void *time, void *callback, void *arg);
extern void func_0200e8c0(void);
extern void func_0200e8cc(void);

int RTC_GetTime_0200e520(void *time)
{
    int result = RTC_GetTimeAsync_0200e4d4(time, (void *)&func_0200e8c0, 0);
    data_02057c0c.lastResult = result;
    if (result == 0) {
        func_0200e8cc();
    }
    return data_02057c0c.lastResult;
}
