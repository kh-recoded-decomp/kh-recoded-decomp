#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern void func_ov001_0209ca00(u32 groupIndex);
extern void func_ov001_0209ca7c(u32 groupIndex);

void func_ov001_02087dfc(u32 groupIndex)
{
    if (g_activeService_0209f2c8 != -1) {
        func_ov001_0209ca00(groupIndex);
        func_ov001_0209ca7c(groupIndex);
    }
}
