#include "nitro/types.h"

typedef struct RtcWork {
    u16 initialized;
    u8 pad_02[2];
    u32 busy;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
} RtcWork;

extern RtcWork data_02057c0c;
extern int func_02004938(void);
extern void func_0200494c(int state);
extern int RTCi_ReadRawTimeAsync_0200e8fc(void);

int RTC_GetTimeAsync_0200e4d4(void *time, void *callback, void *arg)
{
    int state = func_02004938();

    if (data_02057c0c.busy != 0) {
        func_0200494c(state);
        return 1;
    }

    data_02057c0c.busy = 1;
    func_0200494c(state);

    data_02057c0c.unk_18 = 1;
    data_02057c0c.unk_1C = 0;
    data_02057c0c.unk_0C = (u32)time;
    data_02057c0c.unk_08 = (u32)callback;
    data_02057c0c.unk_14 = (u32)arg;

    if (RTCi_ReadRawTimeAsync_0200e8fc() != 0) {
        return 0;
    }

    data_02057c0c.busy = 0;
    return 3;
}
