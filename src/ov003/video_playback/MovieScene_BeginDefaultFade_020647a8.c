#include "nitro/types.h"

extern void MovieScene_BeginFade_02063fa8(u8 mode, s32 target);

int MovieScene_BeginDefaultFade_020647a8(void)
{
    MovieScene_BeginFade_02063fa8(0, 0);
    return 6;
}

