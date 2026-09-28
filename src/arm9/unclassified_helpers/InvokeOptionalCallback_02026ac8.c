#include "nitro/types.h"

typedef void (*Callback)(void);

u32 InvokeOptionalCallback_02026ac8(Callback callback) {
    if (callback != NULL) {
        callback();
    }
    return ~(u32)callback;
}
