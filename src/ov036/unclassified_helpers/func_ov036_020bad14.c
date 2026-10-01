#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_00[6];
    u16 flags;
} PanelWork;

typedef struct PanelManager {
    u32 unk_00;
    PanelWork *work;
} PanelManager;

extern PanelManager data_ov036_020c3920;

int func_ov036_020bad14(void)
{
    data_ov036_020c3920.work->flags &= ~8;
    return -1;
}
