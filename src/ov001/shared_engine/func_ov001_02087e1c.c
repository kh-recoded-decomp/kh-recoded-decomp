#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern void func_ov001_0209caa8(u32 groupIndex);

void func_ov001_02087e1c(u32 groupIndex)
{
    if (g_activeService_0209f2c8 != -1) {
        func_ov001_0209caa8(groupIndex);
    }
}
