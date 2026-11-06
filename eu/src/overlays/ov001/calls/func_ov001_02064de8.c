#include "nitro/types.h"

extern u32 gFieldSessionWork;

void func_ov001_02064de8(void) {
    void (*callback)(void) = *(void (**)(void))(gFieldSessionWork + 0x2838);
    if (callback != NULL) {
        callback();
    }
}
