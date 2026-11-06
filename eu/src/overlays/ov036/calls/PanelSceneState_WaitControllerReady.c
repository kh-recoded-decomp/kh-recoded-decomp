#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_00[6];
    u16 flags;
} PanelWork;

typedef struct PanelManager {
    u32 unk_00;
    PanelWork *work;
} PanelManager;

extern PanelManager gEvent2DPanelManager;
extern int IsTextWindowControllerReady(void);

int PanelSceneState_WaitControllerReady(void)
{
    if (IsTextWindowControllerReady() == 0) {
        return -1;
    }
    gEvent2DPanelManager.work->flags |= 0x8000;
    return 1;
}
