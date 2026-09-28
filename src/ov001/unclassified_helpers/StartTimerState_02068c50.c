#include "nitro/types.h"

typedef struct TimerWork {
    u8 pad_00[0x24];
    u8 enabled;
    u8 pad_25[3];
    u32 startMilliseconds;
} TimerWork;

extern TimerWork *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern u64 func_02003fd4(void);
extern u64 func_02023d54(u64 dividend, u64 divisor);
extern void *func_ov001_02068c88(void);

void *StartTimerState_02068c50(void)
{
    TimerWork *work = NNSi_FndGetCurrentRootHeap_0202a764();

    if (!work->enabled) {
        return NULL;
    }
    work->startMilliseconds = func_02023d54(func_02003fd4() * 64, 0x82ea);
    return func_ov001_02068c88;
}
