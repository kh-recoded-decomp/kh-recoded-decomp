#include "nitro/types.h"

extern u32 gMovieContextState;

void SetAreaSceneDefinitionParams(u8 mode, u16 width, u16 height) {
    u32 base;

    base = gMovieContextState;
    *(u16 *)(gMovieContextState + 0x46) = width;
    *(u16 *)(base + 0x48) = height;
    *(u8 *)(base + 0x1e) = mode;
}
