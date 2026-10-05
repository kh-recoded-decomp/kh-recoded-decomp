#include "nitro/types.h"

extern void *OS_SNPrintf_0202e080(char *dst, unsigned int len, const char *fmt, ...);
extern const char data_ov039_020be9c4[];

u32 FormatPlayTimeText_020be64c(char *buffer, u32 seconds)
{
    if (seconds > 3599999) {
        seconds = 3599999;
    }
    OS_SNPrintf_0202e080(buffer, 10, data_ov039_020be9c4, seconds / 3600, seconds / 60 % 60, seconds % 60);
    return seconds;
}
