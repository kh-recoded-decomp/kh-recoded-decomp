#include "nitro/types.h"

extern u32 data_ov001_020b7760;
extern u32 data_ov033_020b74f0;

void func_ov025_020b617c(void) {
    ((void (*)(u32))&data_ov033_020b74f0)(data_ov001_020b7760 + 25844);
}
