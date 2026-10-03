#include "nitro/types.h"

extern void *data_ov025_020b7760;
extern int func_ov025_020b75e0(void *field);

void ApplySubBgScroll_020b5800(void) {
    u32 offset = func_ov025_020b75e0((u8 *)data_ov025_020b7760 + 0x64f4) & 0x1ff;
    *(vu32 *)0x04001018 = offset;
    *(vu32 *)0x0400101c = offset;
}
