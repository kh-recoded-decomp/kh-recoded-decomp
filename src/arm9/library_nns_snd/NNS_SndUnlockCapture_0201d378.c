#include "nitro/types.h"

extern u32 g_sndCaptureLock_0205d894;

void NNS_SndUnlockCapture_0201d378(u32 capBitFlag)
{
    g_sndCaptureLock_0205d894 &= ~capBitFlag;
}
