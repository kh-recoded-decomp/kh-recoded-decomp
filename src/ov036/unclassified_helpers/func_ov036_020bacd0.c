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
extern void StoreToGlobalPtr4Field28_0202a778(int value);

int func_ov036_020bacd0(void)
{
    data_ov036_020c3920.work->flags &= ~8;
    StoreToGlobalPtr4Field28_0202a778(1);
    data_ov036_020c3920.work->flags |= 0x8000;
    return 7;
}
