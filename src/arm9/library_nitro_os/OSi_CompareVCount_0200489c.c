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

#define HW_LCD_LINES 263

#define VALARM_FUTURE 0
#define VALARM_NOW    1
#define VALARM_PAST   2

s32 OSi_CompareVCount_0200489c(OSVAlarm *alarm, s32 currentFrame, s32 currentVCount)
{
    s32 frameDiff = currentFrame - (s32)alarm->frame;
    s32 vcountDiff = currentVCount - alarm->fire;

    if (frameDiff < 0 || (frameDiff == 0 && vcountDiff < 0)) {
        return VALARM_FUTURE;
    }

    if (vcountDiff < 0) {
        vcountDiff += HW_LCD_LINES;
    }

    return (vcountDiff <= alarm->delay) ? VALARM_NOW : VALARM_PAST;
}
