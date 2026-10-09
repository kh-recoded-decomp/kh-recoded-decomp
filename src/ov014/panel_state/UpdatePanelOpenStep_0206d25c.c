#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcf8a];
    s8 stateIndex;
    s8 closeRequested;
    s8 step;
} PanelState;

extern PanelState *g_panelState_0206f9a0;
extern void func_ov002_02062014(int mode);
extern void StartPanelFadeIn(int mode);
extern BOOL func_ov002_0206655c(void);
extern void ChangePanelState_0206d1c0(s8 nextState);

void UpdatePanelOpenStep_0206d25c(void)
{
    switch (g_panelState_0206f9a0->step) {
    case 0:
        func_ov002_02062014(1);
        g_panelState_0206f9a0->step = 1;
        break;
    case 1:
        StartPanelFadeIn(3);
        g_panelState_0206f9a0->step = 2;
        break;
    case 2:
        if (func_ov002_0206655c()) {
            ChangePanelState_0206d1c0(1);
        }
        break;
    }
}
