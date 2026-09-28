#include "nitro/types.h"

extern u32 data_ov001_020a049c;
extern void func_02029e7c(u32 callerId);

void func_ov001_0206e7c0(void)
{
    u32 ctx;

    ctx = data_ov001_020a049c;
    func_02029e7c(0);
    if (data_ov001_020a049c != 0) {
        *(u32 *)(ctx + 0xf4) = 0;
        *(u8 *)(ctx + 0xf0) = 0;
    }
}
