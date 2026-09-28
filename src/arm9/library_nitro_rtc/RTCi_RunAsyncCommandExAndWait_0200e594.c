#include "nitro/types.h"

typedef struct RtcWork {
    u8 pad_00[0x24];
    int lastResult;
} RtcWork;

extern RtcWork data_02057c0c;
extern int RTCi_StartAsyncCommandEx_0200e544(int arg1, int arg2, void *callback, int arg3);
extern void func_0200e8c0(void);
extern void func_0200e8cc(void);

int RTCi_RunAsyncCommandExAndWait_0200e594(int arg1, int arg2)
{
    int result = RTCi_StartAsyncCommandEx_0200e544(arg1, arg2, (void *)&func_0200e8c0, 0);
    data_02057c0c.lastResult = result;
    if (result == 0) {
        func_0200e8cc();
    }
    return data_02057c0c.lastResult;
}
