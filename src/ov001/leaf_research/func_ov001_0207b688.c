#include "nitro/types.h"

extern u32 data_ov001_020a04c8;
extern s32 func_ov001_02063a38(void);
extern u32 func_ov001_0207b320(BOOL flag);

u32 func_ov001_0207b688(void)
{
    s32 mode;

    if (*(s32 *)(data_ov001_020a04c8 + 0xd8) != 4) {
        return 1;
    }
    mode = func_ov001_02063a38();
    return func_ov001_0207b320(mode == 10);
}
