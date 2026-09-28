#include "nitro/types.h"

extern u32 func_ov001_02087224();
extern void func_ov032_020bfba4();

u32 func_ov016_020a6dd8(u32 unused1, u32 unused2, u32 param3)
{
    u32 context;

    context = func_ov001_02087224();
    func_ov032_020bfba4(context, param3);
    return 1;
}
