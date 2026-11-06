#include "nitro/types.h"

extern u32 gFieldSessionWork;
extern u32 ReleaseSessionHandle();
extern u32 RunPendingCallback();
extern u32 FlushPendingEntryRefresh();

u32 ReleaseSessionTaskAndFlushPendingWork(void) {
    u32 value = gFieldSessionWork;
    ReleaseSessionHandle(gFieldSessionWork, 1);
    RunPendingCallback(value);
    FlushPendingEntryRefresh();
    return 4;
}
