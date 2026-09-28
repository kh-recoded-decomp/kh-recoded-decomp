#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern void func_ov001_0209c744(s16 groupIndex, s32 value);

void func_ov001_02087e80(s16 groupIndex, s32 value)
{
    if (g_activeService_0209f2c8 != -1) {
        func_ov001_0209c744(groupIndex, value);
    }
}
