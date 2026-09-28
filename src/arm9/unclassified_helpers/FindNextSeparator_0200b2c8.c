#include "nitro/types.h"

static inline BOOL IsSjisLeadByte(int c)
{
    return (u32)(((u8)c ^ 0x20) - 0xa1) < 0x3c;
}

static inline BOOL IsSlash(u32 c)
{
    return c == '/' || c == '\\';
}

int FindNextSeparator_0200b2c8(const char *str, int pos)
{
    while (str[pos] != 0 && !IsSlash((u8)str[pos])) {
        pos = pos + 1 + IsSjisLeadByte(str[pos]);
    }
    return pos;
}
