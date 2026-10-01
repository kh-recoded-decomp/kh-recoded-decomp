#include "nitro/types.h"

typedef char *VaList;
#define VA_START(args, last) ((args) = (char *)(((u32)&(last) & ~3U) + 4))

extern u16 *FormatWideTextV_0208c324(const u16 *format, u16 *dest, u32 destLength, VaList args);

u16 *FormatWideText_0208c338(const u16 *format, u16 *dest, u32 destLength, ...)
{
    VaList args;

    VA_START(args, destLength);
    FormatWideTextV_0208c324(format, dest, destLength, args);
    return dest;
}
