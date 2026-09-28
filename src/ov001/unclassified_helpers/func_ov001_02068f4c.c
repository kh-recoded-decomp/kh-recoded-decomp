#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);

u32 func_ov001_02068f4c(void)
{
    u8 *ctx;

    ctx = (u8 *)NNSi_FndGetCurrentRootHeap_0202a764();
    if ((ctx[0x11] & 1) == 0) {
        return 0;
    }
    return 0x2068f65;
}
