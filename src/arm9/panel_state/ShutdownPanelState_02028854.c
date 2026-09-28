#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc];
    void *bufferC;
    void *buffer10;
    u8 pad_14[0x64 - 0x14];
    void *buffer64;
} PanelState;

extern PanelState *g_ptr_0205fe24;
extern void func_02025448(int page, int a, int b);
extern void func_0202a1c4(void *ptr);

void ShutdownPanelState_02028854(void) {
    PanelState *panel = g_ptr_0205fe24;

    if (panel != NULL) {
        func_02025448(0, 0, 0);
        func_02025448(1, 0, 0);
        func_02025448(2, 0, 0);
        func_0202a1c4(panel->buffer64);
        func_0202a1c4(panel->buffer10);
        func_0202a1c4(panel->bufferC);
        func_0202a1c4(panel);
        g_ptr_0205fe24 = NULL;
    }
}
