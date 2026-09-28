#include "nitro/types.h"
#include "nitro/os_types.h"

typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(void *arg);

extern void OS_CreateAlarm(OSAlarm *alarm);
extern void OS_SetAlarm(OSAlarm *alarm, OSTick fire_tick, OSAlarmHandler handler, void *arg);
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int mask);
extern void OS_SleepThread(void *arg);
extern void OSi_SleepAlarmCallback(void *arg);
extern void **data_02056b50[];

void OS_Sleep_02002c78(u32 arg0) {
    char alarm[0x2c];
    void *thread;
    int mask;

    OS_CreateAlarm((OSAlarm *)alarm);
    thread = data_02056b50[2][0];
    mask = OS_DisableInterrupts();
    *(void **)((char *)thread + 0xb0) = alarm;
    OS_SetAlarm((OSAlarm *)alarm, (u64)arg0 * 0x82eaULL >> 6, OSi_SleepAlarmCallback, &thread);
    while (thread != 0) {
        OS_SleepThread(0);
    }
    OS_RestoreInterrupts(mask);
}
