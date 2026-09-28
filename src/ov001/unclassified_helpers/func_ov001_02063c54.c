#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern u32 PXI_Init_0202a638();

void func_ov001_02063c54(void) {
    u32 base = data_ov001_020a0460;
    if (*(s32 *)(data_ov001_020a0460 + 0x27e8) != -1) {
        PXI_Init_0202a638();
        *(u32 *)(base + 0x27e8) = 0xffffffff;
    }
}
