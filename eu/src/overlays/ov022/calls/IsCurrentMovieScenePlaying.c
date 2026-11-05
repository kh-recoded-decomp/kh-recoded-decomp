#include "nitro/types.h"

extern void *GetRunningTaskWork(void);

BOOL IsCurrentMovieScenePlaying(void)
{
    u8 *state = (u8 *)GetRunningTaskWork();

    return *(s32 *)(state + 0x8b0) == 2;
}
