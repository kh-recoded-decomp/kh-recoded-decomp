#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void func_020015a0(void *context, int x, int y, int color, int flags, const void *value);

void func_ov002_020619e8(int param1, int x, int y, int color, const void *value) {
    if (param1 == 0) {
        func_020015a0((u8 *)g_panelState_0206c460 + 0x48, x, y, color, 0, value);
        g_panelState_0206c460->flags10 |= 0x40;
        return;
    }
    func_020015a0((u8 *)g_panelState_0206c460 + 0x7c, x, y, color, 0, value);
    g_panelState_0206c460->flags10 |= 0x80;
}
