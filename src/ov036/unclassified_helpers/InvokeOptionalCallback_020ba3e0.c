#include "nitro/types.h"

typedef void (*Callback)(void);

u32 InvokeOptionalCallback_020ba3e0(Callback callback) {
    if (callback != NULL) {
        callback();
    }
    return ~(u32)callback;
}
