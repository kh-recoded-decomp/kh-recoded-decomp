#include "nitro/types.h"

typedef struct RtcWork {
    u8 pad_00[0x24];
    int lastResult;
} RtcWork;

extern RtcWork data_02057c0c;
extern int RTCi_StartAsyncCommand_0200e468(int arg1, void *callback, int arg2);
extern void func_0200e8c0(void);
extern void func_0200e8cc(void);

int RTCi_RunAsyncCommandAndWait_0200e4b0(int buffer)
{
    int result = RTCi_StartAsyncCommand_0200e468(buffer, (void *)&func_0200e8c0, 0);
    data_02057c0c.lastResult = result;
    if (result == 0) {
        func_0200e8cc();
    }
    return data_02057c0c.lastResult;
}
