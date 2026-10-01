#include "nitro/types.h"

extern u32 data_ov001_020b7760;
extern u32 data_ov033_020b72e8;

void func_ov025_020b6164(void) {
    ((void (*)(u32))&data_ov033_020b72e8)(data_ov001_020b7760 + 25844);
}
