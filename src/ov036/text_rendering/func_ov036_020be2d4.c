#include "nitro/types.h"

typedef char *VaList;
#define VA_START(args, last) ((args) = (char *)(((u32)&(last) & ~3U) + 4))

extern u16 *FormatWideTextV_020be2c0(const u16 *format, u16 *dest, u32 destLength, VaList args);

u16 *func_ov036_020be2d4(const u16 *format, u16 *dest, u32 destLength, ...)
{
    VaList args;

    VA_START(args, destLength);
    FormatWideTextV_020be2c0(format, dest, destLength, args);
    return dest;
}
