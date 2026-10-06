#include "nitro/types.h"

typedef void (*Callback)(void);

u32 func_ov033_020ba400(Callback callback)
{
    if (callback != NULL) {
        callback();
    }
    return ~(u32)callback;
}
