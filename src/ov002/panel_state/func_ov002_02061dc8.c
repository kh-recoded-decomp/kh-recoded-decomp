#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
    u8 pad_11[0x7c - 0x11];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void func_02001768(void *entry, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8);

void func_ov002_02061dc8(int selectSecond, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8) {
    void *entry;

    if (!selectSecond) {
        entry = (u8 *)g_panelState_0206c460 + 0x48;
        g_panelState_0206c460->flags10 |= 0x40;
    } else {
        entry = (u8 *)g_panelState_0206c460 + 0x7c;
        g_panelState_0206c460->flags10 |= 0x80;
    }
    func_02001768(entry, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}
