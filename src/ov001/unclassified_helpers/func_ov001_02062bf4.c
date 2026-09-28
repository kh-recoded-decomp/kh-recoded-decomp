#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern u32 data_ov033_020baadc;

void func_ov001_02062bf4(void) {
    ((void (*)(u32))&data_ov033_020baadc)(data_ov001_020a0460 + 0x280c);
}
