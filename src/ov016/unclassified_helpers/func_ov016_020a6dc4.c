#include "nitro/types.h"

extern u32 func_ov001_02087224();
extern void func_ov016_020a5130();

void func_ov016_020a6dc4(u32 unused1, u32 unused2, u32 param3, u32 param4)
{
    u32 context;

    context = func_ov001_02087224();
    func_ov016_020a5130(context, param3, param4);
}
