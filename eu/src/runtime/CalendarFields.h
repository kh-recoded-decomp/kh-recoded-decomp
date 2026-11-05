#ifndef EU_CALENDAR_FIELDS_H
#define EU_CALENDAR_FIELDS_H

#include "nitro/types.h"

/* Native 36-byte storage preserved by NormalizeCalendarToTime. The first
 * eight words are established by TimeToCalendar; word 8 stays uninterpreted.
 */
typedef struct CalendarFields {
    int second;
    int minute;
    int hour;
    int dayOfMonth;
    int month;
    int yearSince1900;
    int dayOfWeek;
    int dayOfYear;
    u32 reserved20;
} CalendarFields;

typedef char CalendarFieldsSizeCheck[sizeof(CalendarFields) == 36 ? 1 : -1];

long ParseDecimalLong(const char *text);
int IsLeapYearSince1900(int yearSince1900);
int NormalizeCalendarFieldWithCarry(int *field, int divisor, int *carry);
int NormalizeCalendarToTime(CalendarFields *calendar);

#endif
