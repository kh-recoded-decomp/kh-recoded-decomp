#include "nitro/types.h"

typedef struct {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
} CalendarTime;

extern s16 data_02053404[];

extern int func_02022674(int *value, int divisor, int *carry);
extern BOOL func_02021a9c(long *value, long factor);
extern long func_020225c0(int year, int month);
extern BOOL TryAddInt32_02021a50(long *value, long addend);
extern void func_020226b4(u32 time, CalendarTime *tm);

BOOL __msl_mktime_020227fc(CalendarTime *tm, u32 *outTime)
{
    long days;
    u32 seconds;
    u32 daySeconds;

    if (!tm || !outTime) {
        return FALSE;
    }

    --tm->tm_mday;

    if (!func_02022674(&tm->tm_sec, 60, &tm->tm_min)) goto fail;
    if (!func_02022674(&tm->tm_min, 60, &tm->tm_hour)) goto fail;
    if (!func_02022674(&tm->tm_hour, 24, &tm->tm_mday)) goto fail;
    if (!func_02022674(&tm->tm_mon, 12, &tm->tm_year)) goto fail;

    days = tm->tm_year;

    if (!func_02021a9c(&days, 365)) goto fail;
    if (!TryAddInt32_02021a50(&days, func_020225c0(tm->tm_year, tm->tm_mon))) goto fail;
    if (!TryAddInt32_02021a50(&days, data_02053404[tm->tm_mon])) goto fail;
    if (!TryAddInt32_02021a50(&days, tm->tm_mday)) goto fail;

    if (days < 0 || days > (0xFFFFFFFFUL / 86400)) {
        goto fail;
    }

    daySeconds = days * 86400;
    seconds = (tm->tm_hour * 3600) + (tm->tm_min * 60) + tm->tm_sec;

    if (seconds > 0xFFFFFFFFUL - daySeconds) {
        goto fail;
    }

    seconds += daySeconds;
    *outTime = seconds + 0x7c558180;

    func_020226b4(*outTime, tm);

    return TRUE;

fail:
    return FALSE;
}
