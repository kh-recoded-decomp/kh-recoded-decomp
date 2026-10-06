#include "nitro/types.h"

u32 func_ov000_020613e0(void (*callback)(void))
{
    if (callback != 0) {
        callback();
    }
    return ~(u32)callback;
}
