#include "nitro/types.h"

typedef struct {
    u8 _0[0x44];
    int state;
} PanelState;

extern PanelState *data_ov044_020d0ea0;
extern void func_ov044_020d0144(int state);

void ReapplyPanelState_020d0b88(void) {
    func_ov044_020d0144(data_ov044_020d0ea0->state);
}
