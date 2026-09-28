#include "nitro/types.h"

extern u32 func_ov001_020631e4();

u32 func_ov001_02065e8c(s32 entry) {
    func_ov001_020631e4(3);
    *(u32 *)(entry + 0x1cc) = 0;
    return 3;
}
