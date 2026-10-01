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
extern void func_ov036_020ba77c(void);
extern void StoreToGlobalPtr4Field28_0202a778(int value);

int func_ov036_020ba928(void)
{
    PanelWork *work = data_ov036_020c3920.work;

    work->flags |= 8;
    if (work->flags & 1) {
        work->flags &= ~1;
    }
    func_ov036_020ba77c();
    StoreToGlobalPtr4Field28_0202a778(0);
    return 2;
}
