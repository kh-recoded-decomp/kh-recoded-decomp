#include "nitro/types.h"

extern s32 func_ov001_02086d00(void);
extern void func_ov001_02067704(s32 value);

u32 func_ov028_020ba738(void)
{
    s32 value = func_ov001_02086d00();

    if (value != 0) {
        func_ov001_02067704(value);
        return 4;
    }
    return 0xffffffff;
}
