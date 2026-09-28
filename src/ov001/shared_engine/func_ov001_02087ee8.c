#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern void func_ov001_0209c52c(void);

void func_ov001_02087ee8(void)
{
    if (g_activeService_0209f2c8 != -1) {
        func_ov001_0209c52c();
    }
}
