#include "nitro/types.h"

extern u32 gMovieContextState;
extern u32 gAreaRewardSceneWork;
extern int IsScreenModeIdle();
extern int Panel_TryBeginTransition4();

u32 AreaSceneState_WaitForExitTransition(void)
{
    int ready;

    ready = IsScreenModeIdle();
    if (ready == 0) {
        return 0xffffffff;
    }
    if (((*(u16 *)(gMovieContextState + 6) & 0x10) == 0) &&
        (ready = Panel_TryBeginTransition4(), ready == 0)) {
        return 0xffffffff;
    }
    *(u32 *)(gAreaRewardSceneWork + 0x144) = 2;
    return 0x11;
}
