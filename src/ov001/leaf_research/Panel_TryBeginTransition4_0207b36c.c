#include "nitro/types.h"

typedef struct Panel {
    u8 pad_00[0x30];
    s32 state;
    u8 pad_34[0x4];
    s32 inputReady;
    u8 pad_3C[0x1c];
    s32 nextState;
    u8 pad_5C[0x7c];
    s32 transitionType;
    u8 pad_DC[0x8];
    u32 slotIds[4];
} Panel;

extern Panel *g_activePanel_020a04c8;
extern u32 func_ov001_0207b3cc(void);
extern u32 func_ov025_020b6270(s32 index);
extern void SetDisplaySetting_02029f28(int value);
extern void func_ov001_0207b20c(Panel *panel, s32 transitionType);

BOOL Panel_TryBeginTransition4_0207b36c(void)
{
    Panel *panel;
    s32 i;

    panel = g_activePanel_020a04c8;
    if (panel->state == 2) {
        return FALSE;
    }
    if (panel->transitionType == 4) {
        return FALSE;
    }
    if (panel->inputReady == 0) {
        return FALSE;
    }
    if (func_ov001_0207b3cc() == 2) {
        i = 0;
        do {
            panel->slotIds[i] = func_ov025_020b6270(i);
            i++;
        } while (i < 4);
    }
    SetDisplaySetting_02029f28(1);
    func_ov001_0207b20c(panel, 4);
    panel->nextState = 6;
    return TRUE;
}
