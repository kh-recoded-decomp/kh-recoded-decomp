#include "nitro/types.h"

u32 RunProtectionCallback(void (*callback)(void))
{
    if (callback != 0) {
        callback();
    }
    return ~(u32)callback;
}
