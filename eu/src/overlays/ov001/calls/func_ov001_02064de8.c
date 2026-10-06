#include "nitro/types.h"

extern u32 data_ov001_020a0480;

void func_ov001_02064de8(void) {
    void (*callback)(void) = *(void (**)(void))(data_ov001_020a0480 + 0x2838);
    if (callback != NULL) {
        callback();
    }
}
