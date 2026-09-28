#include "nitro/types.h"

extern u32 g_pxiFifoTag_020c36c0;
extern u32 func_0202a78c(u32 tag);

BOOL IsPxiFifoTagSet_020bc414(void)
{
    u32 result;

    result = func_0202a78c(g_pxiFifoTag_020c36c0);
    return result != 0;
}
