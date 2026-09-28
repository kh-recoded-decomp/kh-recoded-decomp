#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x118];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern int func_ov027_020ba2a8(void *state, int index);

int func_ov002_020621c4(int index) {
    return func_ov027_020ba2a8((u8 *)g_panelState_0206c460 + 0x118, index);
}
