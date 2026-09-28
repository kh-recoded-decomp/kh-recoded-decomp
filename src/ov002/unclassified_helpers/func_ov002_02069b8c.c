#include "nitro/types.h"

extern u32 func_ov002_02069dd8(s32 category, u32 param3);
extern u32 func_ov002_02069aac(u32 param1, u32 value, u32 param4);

u32 func_ov002_02069b8c(u32 param1, s32 category, u32 param3, u32 param4) {
    u32 value = func_ov002_02069dd8(category, param3);
    if (category != 0x12) {
        return func_ov002_02069aac(param1, value, param4);
    }
    return 0;
}
