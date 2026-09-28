#include "nitro/types.h"

extern u32 func_ov001_0206db5c();
extern u32 func_ov021_020a75d8();

void func_ov001_02063c94(void) {
    s32 entry = func_ov001_0206db5c(0);
    func_ov021_020a75d8(entry, *(u16 *)(*(s32 *)(entry + 0x1d4) + 4));
}
