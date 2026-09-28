#include "nitro/types.h"

typedef struct PanelFlags {
    u8 unused0 : 4;
    u8 pending0 : 1;
    u8 pending1 : 1;
    u8 unused6 : 2;
} PanelFlags;

typedef struct PanelState {
    u8 pad_00[0x10];
    PanelFlags flags10;
    u8 pad_11[0xb0 - 0x11];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void func_020014f0(void *entry);

void func_ov002_020621e4(void) {
    if (g_panelState_0206c460->flags10.pending0) {
        func_020014f0((u8 *)g_panelState_0206c460 + 0xb0);
    }
    if (g_panelState_0206c460->flags10.pending1) {
        func_020014f0((u8 *)g_panelState_0206c460 + 0xe4);
    }
    g_panelState_0206c460->flags10.pending0 = 0;
    g_panelState_0206c460->flags10.pending1 = 0;
}
