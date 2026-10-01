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
extern int func_ov036_020c2f04(void);

int func_ov036_020ba8f4(void)
{
    if (func_ov036_020c2f04() == 0) {
        return -1;
    }
    data_ov036_020c3920.work->flags |= 0x8000;
    return 1;
}
