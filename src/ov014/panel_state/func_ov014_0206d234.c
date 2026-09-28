#include "nitro/types.h"

extern u32 g_panelState_0206f9a0;
extern void func_ov014_0206ea4c(s32 mode);

void func_ov014_0206d234(void)
{
    func_ov014_0206ea4c(0);
    *(u8 *)(g_panelState_0206f9a0 + 0xcf8c) = 0;
}
