#include "nitro/types.h"

extern u8 *gMovieContextState;

u32 GetAreaSceneTransitionFlag(void)
{
    return *(const u16 *)(gMovieContextState + 0x6) & 0x20;
}
