#include "nitro/types.h"

extern u32 gMovieContextState;

void SetAreaSceneDrawEnabled(int enable) {
    if (enable != 0) {
        *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) | 4;
        return;
    }
    *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) & 0xfffb;
}
