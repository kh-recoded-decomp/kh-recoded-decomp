#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern u32 func_ov001_0206493c();

void func_ov001_02064998(void) {
    func_ov001_0206493c();
    *(u32 *)(data_ov001_020a0460 + 0x214) = *(u32 *)(data_ov001_020a0460 + 0x214) & 0xffffbfff;
}
