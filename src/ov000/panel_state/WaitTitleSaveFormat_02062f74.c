#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66dc];
    u64 formatStartTick;
    BOOL formatResult;
    s32 formatFailed;
} Panel;

extern u64 OS_GetTick_02003fd4(void);
extern void SetPanelState_02061db0(Panel *panel, s32 state, u32 param1, u32 param2);
extern void func_ov000_02061b88(int value, int waitVBlank);

int WaitTitleSaveFormat_02062f74(Panel *panel)
{
    int result = -1;

    if (panel->formatResult == 0) {
        SetPanelState_02061db0(panel, 1, 0, 0);
        panel->formatFailed = 1;
        result = 14;
    } else if (OS_GetTick_02003fd4() >= panel->formatStartTick + 0xffb10) {
        result = 0;
        SetPanelState_02061db0(panel, 0, 0, 30);
        func_ov000_02061b88(0x10, 1);
    }
    return result;
}
