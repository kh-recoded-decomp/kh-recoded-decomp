#include "nitro/types.h"

extern u32 gMovieContextState;
extern int IsScreenModeIdle();
extern void BeginScreenFadeOut();

u32 AreaSceneState_BeginFadeOut(void)
{
    int ready;

    ready = IsScreenModeIdle();
    if (ready == 0) {
        return 0xffffffff;
    }
    BeginScreenFadeOut((int)*(s8 *)(gMovieContextState + 0x1c));
    return 0x10;
}
