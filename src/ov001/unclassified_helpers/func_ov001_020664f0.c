#include "nitro/types.h"

extern u32 func_ov001_02065fa8();
extern u32 func_ov001_020660a0();

u32 func_ov001_020664f0(u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    s32 slot = func_ov001_02065fa8();
    if (slot < 0) {
        return 0;
    }
    return func_ov001_020660a0(slot, arg1, arg2, arg3, arg4);
}
