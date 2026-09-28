#include "nitro/types.h"

extern s32 func_ov001_0207b3cc(void);
extern s32 func_ov001_0207b5f4(void);
extern void func_ov025_020b6328(void);

u32 func_ov001_0207b754(void)
{
    if (func_ov001_0207b3cc() != 2) {
        return 0;
    }
    if (func_ov001_0207b5f4() == 0) {
        return 0;
    }
    func_ov025_020b6328();
    return 1;
}
