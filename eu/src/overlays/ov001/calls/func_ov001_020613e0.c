#include "nitro/types.h"

u32 func_ov001_020613e0(void (*callback)(void)) {
    if (callback != NULL) {
        callback();
    }
    return ~(u32)callback;
}
