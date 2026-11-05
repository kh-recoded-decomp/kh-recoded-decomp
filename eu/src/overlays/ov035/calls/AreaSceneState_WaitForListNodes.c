#include "nitro/types.h"

extern u32 gMovieContextState;
extern int AreAllListNodesReady(void);
extern void RequestFieldEntryResourceDelivery(void);

u32 AreaSceneState_WaitForListNodes(void) {
    if (AreAllListNodesReady() == 0) {
        return 0xffffffff;
    }
    RequestFieldEntryResourceDelivery();
    *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) | 0x8000;
    return 3;
}
