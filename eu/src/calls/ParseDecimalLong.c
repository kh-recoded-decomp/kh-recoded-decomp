#include "src/runtime/CalendarFields.h"

extern long strtol(const char *text, char **end, int base);

long ParseDecimalLong(const char *text)
{
    return strtol(text, NULL, 10);
}
