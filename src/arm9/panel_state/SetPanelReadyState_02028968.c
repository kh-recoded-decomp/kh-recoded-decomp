#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc0];
    s32 state;
} PanelState;

extern PanelState *g_ptr_0205fe24;

void SetPanelReadyState_02028968(int readyA, int readyB) {
    if (readyA != 0 && readyB != 0) {
        g_ptr_0205fe24->state = 0;
        return;
    }
    if (readyA != 0) {
        g_ptr_0205fe24->state = 2;
        return;
    }
    if (readyB != 0) {
        g_ptr_0205fe24->state = 1;
        return;
    }
    g_ptr_0205fe24->state = 3;
}
