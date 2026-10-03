#include "nitro/types.h"

typedef struct {
    u8 _0[0x48];
    u32 pendingState;
} PanelState;

extern PanelState *data_ov044_020d0ea0;
extern void SetPanelState_020d0278(u32 state, u32 data);

void EnterPendingPanelState_020d0d80(u32 data) {
    SetPanelState_020d0278(data_ov044_020d0ea0->pendingState, data);
}
