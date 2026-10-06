#include "nitro/types.h"

extern u32 data_ov025_020b7780;
extern u32 ScrollListDownOneRow;

void func_ov025_020b6184(void) {
    ((void (*)(u32))&ScrollListDownOneRow)(data_ov025_020b7780 + 25844);
}
