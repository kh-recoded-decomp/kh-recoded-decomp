#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_00[6];
    u16 flags;
} PanelWork;

typedef struct PanelManager {
    u32 state;
    PanelWork *work;
} PanelManager;

extern PanelManager data_ov036_020c3940;

int ClearPanelSceneTransition(void)
{
    data_ov036_020c3940.work->flags &= ~8;
    return -1;
}
