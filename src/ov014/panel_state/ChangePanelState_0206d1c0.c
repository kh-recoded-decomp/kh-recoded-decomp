#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcf8a];
    s8 stateIndex;
} PanelState;

typedef struct PanelStateHandlers {
    void (*enter)(void);
    void (*update)(void);
    void (*exit)(void);
} PanelStateHandlers;

extern PanelState *g_panelState_0206f9a0;
extern PanelStateHandlers g_panelStateTable_0206f8f8[];

void ChangePanelState_0206d1c0(s8 nextState)
{
    if (g_panelState_0206f9a0->stateIndex != -1) {
        g_panelStateTable_0206f8f8[g_panelState_0206f9a0->stateIndex].exit();
    }
    g_panelState_0206f9a0->stateIndex = nextState;
    g_panelStateTable_0206f8f8[g_panelState_0206f9a0->stateIndex].enter();
}
