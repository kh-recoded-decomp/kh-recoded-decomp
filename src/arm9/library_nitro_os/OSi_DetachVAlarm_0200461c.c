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

void OSi_DetachVAlarm_0200461c(OSVAlarm *alarm)
{
    OSVAlarm *prev;
    OSVAlarm *next;

    if (!alarm) {
        return;
    }

    next = alarm->next;
    prev = alarm->prev;

    if (next) {
        next->prev = prev;
    } else {
        data_02056eb0.tail = prev;
    }

    if (prev) {
        prev->next = next;
    } else {
        data_02056eb0.head = next;
    }
}
