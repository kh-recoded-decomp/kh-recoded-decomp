#include "nitro/types.h"

extern u32 func_ov001_0207a8fc();
extern void func_ov023_020b6cf4(void);

extern u32 g_activePanel_020a04c8;

void func_ov001_0207b408(void)
{
    u32 ready;

    *(u32 *)(g_activePanel_020a04c8 + 0x50) = 0xfffffffe;
    ready = func_ov001_0207a8fc();
    if (ready != 0) {
        func_ov023_020b6cf4();
    }
}
