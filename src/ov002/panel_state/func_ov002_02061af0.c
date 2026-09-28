#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void func_02001668(void *context, int x, int y, int color, int param5, const void *param6);

void func_ov002_02061af0(int param1, int x, int y, int color, int param5, const void *param6) {
    if (param1 == 0) {
        func_02001668((u8 *)g_panelState_0206c460 + 0x48, x, y, color, param5, param6);
        g_panelState_0206c460->flags10 |= 0x40;
        return;
    }
    func_02001668((u8 *)g_panelState_0206c460 + 0x7c, x, y, color, param5, param6);
    g_panelState_0206c460->flags10 |= 0x80;
}
