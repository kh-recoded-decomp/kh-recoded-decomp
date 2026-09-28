#include "nitro/types.h"

extern u32 g_ov029SoundCtx_020baba0;
extern void func_0204df9c();
extern void PXI_Init_0202a638();
extern void func_ov001_02063c54();

void ShutdownOv029SoundCtx_020ba52c(void)
{
    func_0204df9c(0);
    PXI_Init_0202a638(*(u32 *)(g_ov029SoundCtx_020baba0 + 0xc));
    PXI_Init_0202a638(*(u32 *)(g_ov029SoundCtx_020baba0 + 0x10));
    func_ov001_02063c54();
    g_ov029SoundCtx_020baba0 = 0;
}
