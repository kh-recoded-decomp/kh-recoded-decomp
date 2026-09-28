#include "nitro/types.h"

typedef struct PanelSlot {
    s32 timer;
    s32 mode;
} PanelSlot;

typedef struct PanelState {
    u8 pad_00[0xc];
    u8 pages[0x68];
    PanelSlot slots[2];
    u8 pad_84[0x10];
    s32 selectedSlot;
} PanelState;

extern PanelState *g_ptr_0205fe24;
extern u16 data_02060500;
extern void func_0204d924(u32 a, u32 b);
extern void func_0202849c(void *state, int page, int delta);

BOOL ToggleSelectedPanelSlot_02028104(void)
{
    PanelState *panel = g_ptr_0205fe24;
    int slot;

    if ((data_02060500 & 0x80) || (data_02060500 & 0x40)) {
        func_0204d924(0, 0);
        panel->slots[panel->selectedSlot].mode = 0;
        panel->selectedSlot = (panel->selectedSlot == 0) ? 1 : 0;
        panel->slots[panel->selectedSlot].mode = 1;
        panel->slots[panel->selectedSlot].timer = 0;
        for (slot = 0; slot < 2; slot++) {
            func_0202849c(panel->pages, slot, panel->slots[slot].mode);
        }
        return TRUE;
    }
    return FALSE;
}
