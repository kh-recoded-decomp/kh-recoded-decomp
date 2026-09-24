/* Computes the next periodic deadline and inserts an alarm into the doubly linked queue in deadline order.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/os/calls/func_02003410.c.
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

extern struct { u16 useAlarm; u16 pad; struct OSiAlarmQueue queue; } data_02056ea4;
#define OSi_UseAlarm data_02056ea4.useAlarm
#define OSi_AlarmQueue data_02056ea4.queue
extern void OSi_SetTimer(OSAlarm *alarm);
extern void InsertAlarmByDeadline_02004214(OSAlarm *alarm, OSTick fire);
#define OSi_InsertAlarm InsertAlarmByDeadline_02004214


void InsertAlarmByDeadline_02004214 (OSAlarm * alarm, OSTick fire)
{
    OSAlarm * prev;
    OSAlarm * next;

    if (alarm->period > 0) {
        OSTick tick = OS_GetTick();

        fire = alarm->start;
        if (alarm->start < tick) {
            fire += alarm->period * ((tick - alarm->start) / alarm->period + 1);
        }
    }

    alarm->fire = fire;

    for (next = OSi_AlarmQueue.head; next; next = next->next) {

        if ((s64)(fire - next->fire) >= 0) {
            continue;
        }

        alarm->prev = next->prev;
        next->prev = alarm;
        alarm->next = next;
        prev = alarm->prev;

        if (prev) {
            prev->next = alarm;
        } else {
            OSi_AlarmQueue.head = alarm;
            OSi_SetTimer(alarm);
        }

        return;
    }

    alarm->next = 0;
    prev = OSi_AlarmQueue.tail;
    OSi_AlarmQueue.tail = alarm;
    alarm->prev = prev;

    if (prev) {
        prev->next = alarm;
    } else {
        OSi_AlarmQueue.head = OSi_AlarmQueue.tail = alarm;
        OSi_SetTimer(alarm);
    }
}
