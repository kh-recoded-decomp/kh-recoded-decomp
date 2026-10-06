#include "nitro/types.h"

extern u32 func_ov001_0208724c();
extern void ApplyGroupLeaderHit();

u32 func_ov016_020a6df8(u32 unused1, u32 unused2, u32 param3)
{
    u32 context;

    context = func_ov001_0208724c();
    ApplyGroupLeaderHit(context, param3);
    return 1;
}
