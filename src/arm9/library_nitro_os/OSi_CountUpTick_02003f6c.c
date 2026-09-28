#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/hw.h"

typedef void *OSMessage;

typedef int OSTimer;
#define OS_TIMER_0 0
#define OS_TIMER_PRESCALER_64 (1UL << 0)
#define OSi_TICK_TIMERCONTROL  (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)
#define OSi_TICK_TIMER         OS_TIMER_0

static inline void OS_SetTimerCount(OSTimer id, u16 count)
{
    *((vu16 *)((u32)REG_TM0CNT_L_ADDR + id * 4)) = count;
}

static inline void OS_SetTimerControl(OSTimer id, u16 control)
{
    *((vu16 *)((u32)REG_TM0CNT_H_ADDR + id * 4)) = control;
}

extern struct { u16 useTick; u16 pad; BOOL needResetTimer; volatile u64 tickCounter; } data_02056e94;
#define OSi_NeedResetTimer data_02056e94.needResetTimer
#define OSi_TickCounter data_02056e94.tickCounter
extern void OSi_EnterTimerCallback(int timerNo, void (*callback)(void *), void *arg);

void OSi_CountUpTick_02003f6c(void)
{
    OSi_TickCounter++;

    if (OSi_NeedResetTimer) {
        OS_SetTimerControl(OSi_TICK_TIMER, 0);
        OS_SetTimerCount((OSTimer)OSi_TICK_TIMER, (u16)0);
        OS_SetTimerControl(OSi_TICK_TIMER, (u16)OSi_TICK_TIMERCONTROL);

        OSi_NeedResetTimer = FALSE;
    }

    OSi_EnterTimerCallback(OSi_TICK_TIMER, (void (*)(void *))OSi_CountUpTick_02003f6c, 0);
}
