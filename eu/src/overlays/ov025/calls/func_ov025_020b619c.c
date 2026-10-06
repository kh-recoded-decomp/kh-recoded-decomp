#include "nitro/types.h"

extern u32 data_ov025_020b7780;
extern u32 ResetListToFirstEntry;

void func_ov025_020b619c(void) {
    ((void (*)(u32))&ResetListToFirstEntry)(data_ov025_020b7780 + 25844);
}
