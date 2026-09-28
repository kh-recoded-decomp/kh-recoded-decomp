#include "nitro/types.h"

extern int FreeBufferAndClearStatus_0206a918(int obj);
extern int ZeroHalfThenFree_0202cd78(void *arg0);

extern u32 g_manager_020a0480;

void func_ov001_0206a118(void)
{
    FreeBufferAndClearStatus_0206a918(g_manager_020a0480 + 0x30);
    ZeroHalfThenFree_0202cd78(*(void **)(g_manager_020a0480 + 0x60));
    g_manager_020a0480 = 0;
}
