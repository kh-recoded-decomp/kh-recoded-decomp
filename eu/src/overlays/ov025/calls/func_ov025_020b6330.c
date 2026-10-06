#include "nitro/types.h"

extern u32 data_ov025_020b7780;
extern u32 CountActiveSlots;

void func_ov025_020b6330(void) {
    ((void (*)(u32))&CountActiveSlots)(data_ov025_020b7780 + 25844);
}
