#include "nitro/types.h"

typedef struct PanelObject {
    u8 pad_00[0x94];
    u32 unk_94_0 : 1;
    u32 isActive : 1;
} PanelObject;

typedef struct PanelState {
    u8 pad_00[0x2bc];
    s32 unk_2BC;
    s32 unk_2C0;
    s32 unk_2C4;
    u32 slotFlags;
    u8 pad_2CC[0x22];
    s8 selectedSlot;
    u8 pad_2EF[0x6818 - 0x2ef];
    u8 panel[1];
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern PanelObject *func_ov027_020b90a4(void *panel, int id);
extern void func_ov027_020b95e4(void *panel, PanelObject *object);
extern void func_ov027_020b96a0(void *panel, PanelObject *object, int mode);

void RefreshSelectedSlotFlags_02072c18(void) {
    void *panel;
    PanelObject *object;

    g_panelState_02074ce0->unk_2BC = 0;
    g_panelState_02074ce0->unk_2C0 = 0;
    g_panelState_02074ce0->unk_2C4 = 0;
    g_panelState_02074ce0->slotFlags = 0;
    if (func_ov027_020b90a4(g_panelState_02074ce0->panel, g_panelState_02074ce0->selectedSlot + 201)->isActive) {
        g_panelState_02074ce0->slotFlags |= 1;
    }
    if (func_ov027_020b90a4(g_panelState_02074ce0->panel, g_panelState_02074ce0->selectedSlot + 101)->isActive) {
        g_panelState_02074ce0->slotFlags |= 2;
    }
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 5);
    func_ov027_020b95e4(panel, object);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 5);
    func_ov027_020b96a0(panel, object, 0);
}
