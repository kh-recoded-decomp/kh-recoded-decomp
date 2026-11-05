#include "nitro/types.h"

u32 InvokeOptionalCallbackAndComplementAddress(void (*callback)(void)) {
    if (callback != NULL) {
        callback();
    }
    return ~(u32)callback;
}
