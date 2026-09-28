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
extern void OSi_VAlarmSetTimer_020046f4(OSVAlarm *alarm);
extern void OSi_AppendVAlarm_020045e4(OSVAlarm *alarm);

void OSi_InsertVAlarm_02004568(OSVAlarm *alarm)
{
    OSVAlarm *prev;
    OSVAlarm *next;

    for (next = data_02056eb0.head; next; next = next->next) {
        if (next->frame < alarm->frame) {
            continue;
        }
        if (next->frame == alarm->frame && next->fire <= alarm->fire) {
            continue;
        }

        prev = next->prev;
        alarm->prev = prev;
        alarm->next = next;
        next->prev = alarm;
        if (prev) {
            prev->next = alarm;
        } else {
            data_02056eb0.head = alarm;
            OSi_VAlarmSetTimer_020046f4(alarm);
        }
        return;
    }

    OSi_AppendVAlarm_020045e4(alarm);
}
