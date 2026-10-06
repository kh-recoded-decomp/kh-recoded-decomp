#include "nitro/types.h"

extern u32 data_ov001_020a04ec;
extern void NNS_SndPlayerPause_0207b80c();

void func_ov001_0207b868(void)
{
    u8 *context;

    context = (u8 *)data_ov001_020a04ec;
    NNS_SndPlayerPause_0207b80c(context + 0xc);
    NNS_SndPlayerPause_0207b80c(context + 8);
    data_ov001_020a04ec = 0;
}
