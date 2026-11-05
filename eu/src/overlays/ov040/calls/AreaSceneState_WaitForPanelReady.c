#include "nitro/types.h"

extern u32 gMovieContextState;
extern int RequestSubsceneMode0Or1FromMode4();
extern void StoreToGlobalPtr4Field28();

u32 AreaSceneState_WaitForPanelReady(void)
{
    int ready;

    ready = RequestSubsceneMode0Or1FromMode4();
    if (ready == 0) {
        return 0xffffffff;
    }
    if ((*(u16 *)(gMovieContextState + 6) & 1) != 0) {
        *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) & 0xfffe;
    }
    StoreToGlobalPtr4Field28(0);
    return 5;
}
