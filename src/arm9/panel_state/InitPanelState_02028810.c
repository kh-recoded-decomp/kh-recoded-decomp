#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x8c];
    s32 field_8c;
    u8 pad_90[0x10];
    s32 field_a0;
    u8 pad_a4[0x1c];
    s32 state;
} PanelState;

extern PanelState *g_ptr_0205fe24;
extern void *func_0202a178(int size);
extern void func_01ff8830(void *dst, int value, int size);
extern void func_020282bc(void);
extern void func_02028548(void);

void InitPanelState_02028810(void) {
    PanelState *panel;

    if (g_ptr_0205fe24 == NULL) {
        panel = func_0202a178(200);
        g_ptr_0205fe24 = panel;
        func_01ff8830(panel, 0, 200);
        panel->field_a0 = -8;
        panel->field_8c = -1;
        func_020282bc();
        func_02028548();
        panel->state = 3;
    }
}
