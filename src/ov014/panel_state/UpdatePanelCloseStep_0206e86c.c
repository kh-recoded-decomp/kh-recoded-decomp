#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcf8a];
    s8 stateIndex;
    s8 closeRequested;
    s8 step;
} PanelState;

extern PanelState *g_panelState_0206f9a0;
extern void StartPanelFadeOut(int mode);
extern BOOL func_ov002_0206655c(void);

void UpdatePanelCloseStep_0206e86c(void)
{
    switch (g_panelState_0206f9a0->step) {
    case 0:
        g_panelState_0206f9a0->step = 1;
        break;
    case 1:
        StartPanelFadeOut(3);
        g_panelState_0206f9a0->step = 2;
        break;
    case 2:
        if (func_ov002_0206655c()) {
            g_panelState_0206f9a0->closeRequested = 1;
            g_panelState_0206f9a0->step = -1;
        }
        break;
    }
}
