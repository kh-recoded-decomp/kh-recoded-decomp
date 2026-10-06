#include "nitro/types.h"

extern u32 func_ov001_0208724c();
extern void DispatchActorCollision();

void func_ov016_020a6de4(u32 unused1, u32 unused2, u32 param3, u32 param4)
{
    u32 context;

    context = func_ov001_0208724c();
    DispatchActorCollision(context, param3, param4);
}
