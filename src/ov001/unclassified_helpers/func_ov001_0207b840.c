#include "nitro/types.h"

extern u32 data_ov001_020a04cc;
extern void NNS_SndPlayerPause_0207b7e4();

void func_ov001_0207b840(void)
{
    u8 *context;

    context = (u8 *)data_ov001_020a04cc;
    NNS_SndPlayerPause_0207b7e4(context + 0xc);
    NNS_SndPlayerPause_0207b7e4(context + 8);
    data_ov001_020a04cc = 0;
}
