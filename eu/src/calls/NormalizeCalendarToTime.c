#include "src/runtime/CalendarFields.h"

/* The existing converter operates on the established calendar prefix. */
extern int __msl_mktime(void *calendar, int *result);

int NormalizeCalendarToTime(CalendarFields *calendar)
{
    CalendarFields local;
    int result;
    local = *calendar;
    if (__msl_mktime(&local, &result) != 0) {
        *calendar = local;
        return result;
    }
    return -1;
}
