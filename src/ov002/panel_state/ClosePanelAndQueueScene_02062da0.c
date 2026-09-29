#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 disabled : 1;
    u8 unk_10_1 : 7;
} PanelState;

extern PanelState *g_panelState_0206c460;

extern void func_0204d7f4(int new_value);
extern void SetPendingScene_02025644(s32 pendId, s32 pendArg);

void ClosePanelAndQueueScene_02062da0(void)
{
    func_0204d7f4(0x14);
    SetPendingScene_02025644(1, -2);
    g_panelState_0206c460->disabled = 1;
}
