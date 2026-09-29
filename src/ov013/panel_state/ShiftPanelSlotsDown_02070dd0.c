#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[2];
    s8 slotCount;
    u8 pad_03[0x254];
    u8 slots[1];
} PanelState;

extern PanelState *g_panelState_02074ce0;

void ShiftPanelSlotsDown_02070dd0(s32 index) {
    while (index < g_panelState_02074ce0->slotCount - 1) {
        if ((index + 1) % 10 == 0) {
            g_panelState_02074ce0->slots[index] = g_panelState_02074ce0->slots[index + 2];
        } else {
            g_panelState_02074ce0->slots[index + 1] = g_panelState_02074ce0->slots[index + 2];
        }
        index++;
    }
}
