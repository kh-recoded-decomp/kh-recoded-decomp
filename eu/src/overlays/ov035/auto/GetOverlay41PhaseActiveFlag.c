#include "nitro/types.h"

extern u8 *gMovieContextState;

u32 GetOverlay41PhaseActiveFlag(void)
{
    return *(const u16 *)(gMovieContextState + 0x6) & 0x40;
}
