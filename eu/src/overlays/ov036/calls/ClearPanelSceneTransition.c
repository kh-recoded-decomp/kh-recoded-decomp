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

int ClearPanelSceneTransition(void)
{
    gEvent2DPanelManager.work->flags &= ~8;
    return -1;
}
