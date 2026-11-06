#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_00[6];
    u16 flags;
} PanelWork;

typedef struct PanelManager {
    u32 state;
    PanelWork *work;
} PanelManager;

extern PanelManager gEvent2DPanelManager;
extern void InitializePanelArchive(void);
extern void StoreToGlobalPtr4Field28(int value);

int StartPanelSceneLoad(void)
{
    PanelWork *work = gEvent2DPanelManager.work;

    work->flags |= 8;
    if (work->flags & 1) {
        work->flags &= ~1;
    }
    InitializePanelArchive();
    StoreToGlobalPtr4Field28(0);
    return 2;
}
