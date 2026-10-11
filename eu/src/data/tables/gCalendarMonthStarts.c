#include "nitro/types.h"

/* Cumulative day offsets for the twelve months and end-of-year sentinel.
 * Row 0 is an ordinary year; row 1 is a leap year. */
const s16 gCalendarMonthStarts[2][13] = {
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 },
};
