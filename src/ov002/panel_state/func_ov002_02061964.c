#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x11];
    union {
        struct {
            u8 slotCTriggered : 1;
            u8 slotDTriggered : 1;
            u8 pad_2 : 6;
        } bits;
        u8 value;
    } flags11;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void func_020015a0(void *context, int x, int y, int color, int flags, const void *value);

void func_ov002_02061964(int param1, int x, int y, int color, const void *value) {
    if (param1 == 0) {
        func_020015a0((u8 *)g_panelState_0206c460 + 0xb0, x, y, color, 0, value);
        g_panelState_0206c460->flags11.bits.slotCTriggered = 1;
        return;
    }
    func_020015a0((u8 *)g_panelState_0206c460 + 0xe4, x, y, color, 0, value);
    g_panelState_0206c460->flags11.value |= 2;
}
