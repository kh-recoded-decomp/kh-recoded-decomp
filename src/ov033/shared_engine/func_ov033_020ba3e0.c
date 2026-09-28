#include "nitro/types.h"

typedef void (*Callback)(void);

u32 func_ov033_020ba3e0(Callback callback)
{
    if (callback != NULL) {
        callback();
    }
    return ~(u32)callback;
}
