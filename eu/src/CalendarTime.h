#ifndef KH_RECODED_CALENDAR_TIME_H
#define KH_RECODED_CALENDAR_TIME_H

#include "nitro/types.h"

/* The nine-word broken-down time layout used by the runtime's mktime wrapper. */
typedef struct CalendarTime {
    s32 second;
    s32 minute;
    s32 hour;
    s32 day;
    s32 month;
    s32 year;
    s32 weekday;
    s32 yearDay;
    s32 daylightSaving;
} CalendarTime;

typedef char CalendarTimeSizeCheck[(sizeof(CalendarTime) == 36) ? 1 : -1];

extern const CalendarTime gCalendarTimeTemplate;

#endif
