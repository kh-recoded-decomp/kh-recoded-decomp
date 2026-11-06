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
extern void StoreToGlobalPtr4Field28(int value);

int FinishPanelSceneTransition(void)
{
    gEvent2DPanelManager.work->flags &= ~8;
    StoreToGlobalPtr4Field28(1);
    gEvent2DPanelManager.work->flags |= 0x8000;
    return 7;
}
