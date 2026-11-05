#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern u32 ReleaseSessionHandle();
extern u32 RunPendingCallback();
extern u32 FlushPendingEntryRefresh();

u32 ReleaseSessionTaskAndFlushPendingWork(void) {
    u32 value = data_ov001_020a0480;
    ReleaseSessionHandle(data_ov001_020a0480, 1);
    RunPendingCallback(value);
    FlushPendingEntryRefresh();
    return 4;
}
