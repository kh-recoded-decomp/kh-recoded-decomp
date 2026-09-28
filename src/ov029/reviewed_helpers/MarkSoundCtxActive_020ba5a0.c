#include "nitro/types.h"

extern u32 g_ov029SoundCtx_020baba0;
extern void func_ov001_02063404();

int MarkSoundCtxActive_020ba5a0(void)
{
    func_ov001_02063404();
    *(u16 *)(g_ov029SoundCtx_020baba0 + 6) = *(u16 *)(g_ov029SoundCtx_020baba0 + 6) | 0x8000;
    return 2;
}
