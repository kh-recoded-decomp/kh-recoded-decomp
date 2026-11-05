#include "nitro/types.h"

extern u32 gMovieContextState;

void RequestAreaSceneExit(u8 value) {
    *(u8 *)(gMovieContextState + 0x1c) = value;
    *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) | 0x4000;
}
