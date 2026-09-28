#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x11];
    u8 flags11;
    u8 pad_12[0xb0 - 0x12];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void func_02001574(void *entry, int mode);

void func_ov002_020620fc(int selector) {
    switch (selector) {
    case -1:
        func_02001574((u8 *)g_panelState_0206c460 + 0xb0, 0);
        func_02001574((u8 *)g_panelState_0206c460 + 0xe4, 0);
        g_panelState_0206c460->flags11 = (g_panelState_0206c460->flags11 & ~0x01) | 0x01;
        g_panelState_0206c460->flags11 |= 0x02;
        return;
    case 0:
        func_02001574((u8 *)g_panelState_0206c460 + 0xb0, 0);
        g_panelState_0206c460->flags11 = (g_panelState_0206c460->flags11 & ~0x01) | 0x01;
        return;
    case 1:
        func_02001574((u8 *)g_panelState_0206c460 + 0xe4, 0);
        g_panelState_0206c460->flags11 |= 0x02;
        return;
    }
}
