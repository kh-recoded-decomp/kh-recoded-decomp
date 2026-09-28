#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66d8];
    u32 busy;
} Panel;

extern int func_0204ded4(int flag);
extern void SetPanelState_02061db0(Panel *panel, s32 state, u32 param1, u32 param2);

u32 TryEnterPanelState_02062a10(Panel *panel)
{
    u32 result = 0xffffffff;

    if (func_0204ded4(1) == 0) {
        panel->busy = 1;
        SetPanelState_02061db0(panel, 1, 0, 0);
        result = 0xc;
    }
    return result;
}
