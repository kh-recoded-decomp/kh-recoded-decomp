#include "nitro/types.h"

extern s32 func_ov001_02086d00(void);
extern void func_ov001_02067704(void);

u32 func_ov030_020ba5f4(void)
{
    s32 ready;

    ready = func_ov001_02086d00();
    if (ready == 0) {
        return 0xffffffff;
    }
    func_ov001_02067704();
    return 4;
}
