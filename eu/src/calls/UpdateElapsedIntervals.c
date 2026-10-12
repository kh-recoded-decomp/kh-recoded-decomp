#include "nitro/types.h"
#include "src/CalendarTime.h"

/* Packed save timestamp and countdown; one interval is three hours. */
typedef struct HardwareDate { s32 year, month, day, weekday; } HardwareDate;
typedef struct HardwareTime { s32 hour, minute, second; } HardwareTime;

typedef struct TimedSessionData {
    u8 reserved00[0x1ac8];
    u32 reservedDay : 27;
    u32 day : 5;
    u32 second : 6;
    u32 remainingIntervals : 7;
    u32 year : 7;
    u32 minute : 6;
    u32 hour : 6;
    u32 month : 4;
    u32 reservedMonth : 28;
} TimedSessionData;

typedef struct TimedSession {
    u8 reserved00[0xcb4];
    TimedSessionData data;
} TimedSession;
typedef struct SessionRoot {
    u8 reserved00[12];
    TimedSession *session;
} SessionRoot;
typedef char TimedSessionDataSizeCheck[(sizeof(TimedSessionData) == 0x1ad4) ? 1 : -1];

extern SessionRoot data_0205fe00;
extern s32 func_020229dc(CalendarTime *time);
extern s32 RTC_GetDateTime(HardwareDate *date, HardwareTime *time);
extern double ComputeSignedDifferenceAsDouble(s32 end, s32 start);

void UpdateElapsedIntervals(void)
{
    TimedSessionData *data = &data_0205fe00.session->data;
    CalendarTime calendar;
    HardwareDate date;
    HardwareTime time;
    s32 previous, current, remaining;
    double intervals;

    calendar.second = data->second;
    calendar.minute = data->minute;
    calendar.hour = data->hour;
    calendar.day = data->day;
    calendar.month = data->month - 1;
    calendar.year = data->year + 100;
    calendar.daylightSaving = -1;
    previous = func_020229dc(&calendar);
    if (previous == -1) {
        data->remainingIntervals = 0;
        return;
    }
    RTC_GetDateTime(&date, &time);
    calendar.second = time.second;
    calendar.minute = time.minute;
    calendar.hour = time.hour;
    calendar.day = date.day;
    calendar.month = date.month - 1;
    calendar.year = date.year + 100;
    calendar.daylightSaving = -1;
    current = func_020229dc(&calendar);
    if (current == -1) {
        data->remainingIntervals = 0;
        return;
    }
    if (current < previous) {
        data->remainingIntervals = 0;
        return;
    }
    intervals = ComputeSignedDifferenceAsDouble(current, previous) / 10800.0;
    if ((s32)intervals == 0) {
        return;
    }
    remaining = data->remainingIntervals;
    if (intervals > 0.0) {
        remaining -= (s32)intervals;
    }
    if (remaining < 0) {
        remaining = 0;
    }
    data->remainingIntervals = remaining;
    data->year = date.year;
    data->month = date.month;
    data->day = date.day;
    data->hour = time.hour;
    data->minute = time.minute;
    data->second = time.second;
}
