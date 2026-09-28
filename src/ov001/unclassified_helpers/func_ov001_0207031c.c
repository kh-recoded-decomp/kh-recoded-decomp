#include "nitro/types.h"

extern void func_ov001_0206fe7c(u32 context);
extern s32 func_ov001_0206feb4(u32 context);

void func_ov001_0207031c(u32 context)
{
    s32 ready;

    ready = func_ov001_0206feb4(context + 0x550);
    if (ready == 0) {
        func_ov001_0206fe7c(context + 0x550);
    }
}
