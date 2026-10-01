#include "nitro/types.h"

typedef u64 OSTick;

typedef struct TimedWindow {
    u8 pad_00[0x84];
    OSTick startTick;
} TimedWindow;

extern OSTick OS_GetTick_02003fd4(void);
extern void func_ov001_02079f70(TimedWindow *window);

void CheckTimerExpired_0207a0e8(TimedWindow *window)
{
    if (OS_GetTick_02003fd4() >= window->startTick + 0x3fec4) {
        func_ov001_02079f70(window);
    }
}
