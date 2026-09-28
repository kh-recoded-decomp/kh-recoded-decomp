#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
    u8 pad_11[0x7c - 0x11];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void func_02001574(void *entry, int mode);

void func_ov002_0206203c(int selector) {
    switch (selector) {
    case -1:
        func_02001574((u8 *)g_panelState_0206c460 + 0x48, 0);
        func_02001574((u8 *)g_panelState_0206c460 + 0x7c, 0);
        g_panelState_0206c460->flags10 |= 0x80;
        g_panelState_0206c460->flags10 |= 0x40;
        return;
    case 0:
        func_02001574((u8 *)g_panelState_0206c460 + 0x48, 0);
        g_panelState_0206c460->flags10 |= 0x40;
        return;
    case 1:
        func_02001574((u8 *)g_panelState_0206c460 + 0x7c, 0);
        g_panelState_0206c460->flags10 |= 0x80;
        return;
    }
}
