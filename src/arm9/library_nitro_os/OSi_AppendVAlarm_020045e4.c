#include "nitro/types.h"

typedef void (*OSVAlarmHandler)(void *arg);

typedef struct OSVAlarm {
    OSVAlarmHandler handler;
    void *arg;
    u32 tag;
    u32 frame;
    s16 fire;
    s16 delay;
    struct OSVAlarm *prev;
    struct OSVAlarm *next;
    BOOL period;
    s16 start;
    BOOL canceled;
} OSVAlarm;

typedef struct {
    u16 useVAlarm;
    s32 previousVCount;
    s32 frame;
    OSVAlarm *head;
    OSVAlarm *tail;
} OSiVAlarmState;

extern OSiVAlarmState data_02056eb0;
extern void func_020046f4(void);

void OSi_AppendVAlarm_020045e4(OSVAlarm *alarm)
{
    OSVAlarm *tail = data_02056eb0.tail;

    alarm->prev = tail;
    alarm->next = NULL;
    data_02056eb0.tail = alarm;

    if (tail) {
        tail->next = alarm;
    } else {
        data_02056eb0.head = alarm;
        func_020046f4();
    }
}
