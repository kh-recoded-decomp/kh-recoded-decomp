#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x98];
    u8 flags;
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern int func_ov027_020b90a4(void *panel, int value);
extern void func_ov027_020b9580(void *panel, int value, int flag);

void func_ov013_02070aa0(void) {
    g_panelState_02074ce0->flags |= 4;
    int result = func_ov027_020b90a4((u8 *)g_panelState_02074ce0 + 0x6818, 9);
    func_ov027_020b9580((u8 *)g_panelState_02074ce0 + 0x6818, result, 0);
    result = func_ov027_020b90a4((u8 *)g_panelState_02074ce0 + 0x6818, 10);
    func_ov027_020b9580((u8 *)g_panelState_02074ce0 + 0x6818, result, 0);
}
