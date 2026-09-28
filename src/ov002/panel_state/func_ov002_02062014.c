#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
} PanelState;

extern PanelState *g_panelState_0206c460;

void func_ov002_02062014(int value) {
    u8 byteValue = (u8)value;
    g_panelState_0206c460->flags10 =
        (g_panelState_0206c460->flags10 & ~0x02) | (((u32)byteValue << 31) >> 30);
}
