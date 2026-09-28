#include "nitro/types.h"

typedef void (*OSIrqFunction)(void *arg);

typedef struct {
    OSIrqFunction pfnHandler;
    u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern OSiIrqSlot data_02056ae8[];
extern u32 OS_EnableIrqMask(u32 mask);

#define OS_IRQ_TIMER0_BIT  3
#define OSi_TimerSlots     (&data_02056ae8[4])

void OSi_EnterTimerCallback_02001eec(u32 timerNo, OSIrqFunction function, void *arg)
{
    OSi_TimerSlots[timerNo].pfnHandler = function;
    OSi_TimerSlots[timerNo].pArg = arg;

    OS_EnableIrqMask(1 << (timerNo + OS_IRQ_TIMER0_BIT));

    OSi_TimerSlots[timerNo].bKeepEnabled = 1;
}
