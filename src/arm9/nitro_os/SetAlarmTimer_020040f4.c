/* Programs timer 1 for the next alarm deadline, installs its callback, and enables its interrupt.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/os/calls/OSi_SetTimer.c.
 * Built with the project pinned flags, without source pragmas. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000



typedef u64 OSTick;
typedef int OSTimer;
typedef u32 OSIrqMask;
typedef void (*OSAlarmHandler)(void *);
typedef struct OSAlarm OSAlarm;

struct OSAlarm {
    OSAlarmHandler handler;
    void *arg;
    u32 tag;
    OSTick fire;
    OSAlarm *prev;
    OSAlarm *next;
    OSTick period;
    OSTick start;
};

struct OSiAlarmQueue {
    OSAlarm *head;
    OSAlarm *tail;
};

#define OS_TIMER_1 1
#define OS_TIMER_PRESCALER_64 (1UL << 0)
#define REG_OS_TM0CNT_H_E_MASK 0x0080
#define REG_OS_TM0CNT_H_I_MASK 0x0040
#define OSi_ALARM_TIMERCONTROL    (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)
#define OSi_ALARM_TIMER           OS_TIMER_1
#define OSi_ALARM_IE_TIMER        (1UL << 4)
#define REG_TM0CNT_L_ADDR         0x04000100
#define REG_TM0CNT_H_ADDR         0x04000102

static inline void OS_SetTimerCount(OSTimer id, u16 count)
{
    *((vu16 *)((u32)REG_TM0CNT_L_ADDR + id * 4)) = count;
}

static inline void OS_SetTimerControl(OSTimer id, u16 control)
{
    *((vu16 *)((u32)REG_TM0CNT_H_ADDR + id * 4)) = control;
}


typedef struct {
    u8 reserved[0x3fc0];
    u8 sysrv[0x38];
    vu32 intr_check;
} OSDtcm;
extern OSDtcm data_027e0000;
static inline void OS_SetIrqCheckFlag(OSIrqMask intr)
{
    data_027e0000.intr_check |= (u32)intr;
}

extern OSTick func_02003fd4(void);
#define OS_GetTick func_02003fd4
extern void OSi_EnterTimerCallback(int timerNo, void (*callback)(void *), void *arg);
extern OSIrqMask OS_EnableIrqMask(OSIrqMask intr);
extern OSIrqMask OS_DisableIrqMask(OSIrqMask intr);
extern void OSi_AlarmHandler(void *arg);

extern struct { u16 useAlarm; u16 pad; struct OSiAlarmQueue queue; } data_02044674;
#define OSi_UseAlarm data_02044674.useAlarm
#define OSi_AlarmQueue data_02044674.queue
extern void SetAlarmTimer_020040f4(OSAlarm *alarm);
extern void func_02003410(OSAlarm *alarm, OSTick fire);
#define OSi_InsertAlarm func_02003410


void SetAlarmTimer_020040f4 (OSAlarm * alarm)
{
    s64 delta;
    OSTick tick = OS_GetTick();
    u16 timerCount;

    OS_SetTimerControl(OSi_ALARM_TIMER, 0);
    delta = (s64)(alarm->fire - tick);
    OSi_EnterTimerCallback(OSi_ALARM_TIMER, OSi_AlarmHandler, NULL);

    if (delta < 0) {
        timerCount = (u16) ~1;
    } else if (delta < 0x10000)   {
        timerCount = (u16)(~delta);
    } else {
        timerCount = 0;
    }

    OS_SetTimerCount((OSTimer)OSi_ALARM_TIMER, timerCount);
    OS_SetTimerControl(OSi_ALARM_TIMER, (u16)OSi_ALARM_TIMERCONTROL);

    (void)OS_EnableIrqMask(OSi_ALARM_IE_TIMER);
}
