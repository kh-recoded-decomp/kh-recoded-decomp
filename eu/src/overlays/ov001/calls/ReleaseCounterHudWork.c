#include "nitro/types.h"

extern u32 gCounterHudWork;
extern void NNS_SndPlayerPause_0207b80c();

void ReleaseCounterHudWork(void)
{
    u8 *context;

    context = (u8 *)gCounterHudWork;
    NNS_SndPlayerPause_0207b80c(context + 0xc);
    NNS_SndPlayerPause_0207b80c(context + 8);
    gCounterHudWork = 0;
}
