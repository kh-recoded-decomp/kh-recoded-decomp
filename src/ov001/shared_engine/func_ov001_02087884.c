#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern void func_ov001_0209c884(void);

void func_ov001_02087884(void)
{
    if (g_activeService_0209f2c8 != -1) {
        func_ov001_0209c884();
    }
}
