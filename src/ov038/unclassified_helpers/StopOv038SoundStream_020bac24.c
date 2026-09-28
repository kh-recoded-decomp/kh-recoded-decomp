#include "nitro/types.h"

extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);

BOOL StopOv038SoundStream_020bac24(void)
{
    StopSoundStreamAtIndex_0204deb0(0, 0);
    return TRUE;
}
