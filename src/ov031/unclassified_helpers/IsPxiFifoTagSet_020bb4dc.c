#include "nitro/types.h"

extern u32 g_pxiFifoTag_020bc780;
extern u32 func_0202a78c(u32 tag);

u32 IsPxiFifoTagSet_020bb4dc(void)
{
    u32 result;

    result = func_0202a78c(g_pxiFifoTag_020bc780);
    if (result != 0) {
        return 1;
    }
    return 0;
}
