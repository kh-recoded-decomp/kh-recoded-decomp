#include "nitro/types.h"

typedef u64 OSTick;

typedef struct TweenChannels {
    int values[8];
    u16 activeMask;
    s16 channel3Speed;
    u8 running;
    u8 pad_25[3];
    u32 lastMilliseconds;
} TweenChannels;

extern TweenChannels *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern OSTick OS_GetTick_02003fd4(void);
extern void *func_ov001_02068c50(void);

void *AdvanceTweenChannels_02068c88(void)
{
    TweenChannels *tween = NNSi_FndGetCurrentRootHeap_0202a764();
    u32 now;
    int i;
    u32 delta;

    if (!tween->running) {
        return func_ov001_02068c50;
    }
    now = (OS_GetTick_02003fd4() * 64) / 0x82ea;
    delta = now - tween->lastMilliseconds;
    for (i = 0; i < 8; i++) {
        if (tween->activeMask & (1 << i)) {
            if (i >= 3 && i < 4) {
                tween->values[i] += (delta * tween->channel3Speed) >> 12;
            } else {
                tween->values[i] += delta;
            }
        }
    }
    tween->lastMilliseconds = now;
    return NULL;
}
