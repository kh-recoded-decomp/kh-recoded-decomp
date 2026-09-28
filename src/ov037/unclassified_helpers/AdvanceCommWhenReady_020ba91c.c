#include "nitro/types.h"

extern s32 func_ov037_020bb4bc(void);
extern s32 func_ov001_0206a814(void);
extern void func_ov001_0206a7c0(int flag);

s32 AdvanceCommWhenReady_020ba91c(void)
{
    s32 ready;

    func_ov037_020bb4bc();
    ready = func_ov001_0206a814();
    if (ready != 0) {
        func_ov001_0206a7c0(1);
        return 8;
    }
    return -1;
}
