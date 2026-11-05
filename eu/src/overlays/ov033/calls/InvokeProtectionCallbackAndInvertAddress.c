#include "nitro/types.h"

typedef void (*Callback)(void);

u32 InvokeProtectionCallbackAndInvertAddress(Callback callback)
{
    if (callback != NULL) {
        callback();
    }
    return ~(u32)callback;
}
