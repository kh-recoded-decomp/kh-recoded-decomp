#include "nitro/types.h"

extern u32 gFieldSessionWork;

u32 func_ov001_02065f04(void) {
    *(u8 *)(gFieldSessionWork + 0x27b6) = *(u8 *)(gFieldSessionWork + 0x27b6) | 0x20;
    return 1;
}
