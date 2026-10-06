#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern u32 PXI_Init_0202a64c();

void func_ov001_02063c54(void) {
    u32 base = data_ov001_020a0480;
    if (*(s32 *)(data_ov001_020a0480 + 0x27e8) != -1) {
        PXI_Init_0202a64c();
        *(u32 *)(base + 0x27e8) = 0xffffffff;
    }
}
