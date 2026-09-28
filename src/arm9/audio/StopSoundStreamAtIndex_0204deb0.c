#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern void NNS_SndArcStrmStop_020202e0(void *handle, int fadeFrame);

void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame)
{
    NNS_SndArcStrmStop_020202e0(g_soundWork_0206084c + 0xb44c0 + handleIndex * 4, fadeFrame);
}
