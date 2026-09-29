#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0x4c];
    u8 animator[0x4c];
    u8 objectList[0x647c];
    u8 entryList[0x6a76];
    s8 stateIndex;
    s8 result;
} PanelState;

typedef struct PanelStateHandlers {
    void (*enter)(void);
    void (*update)(void);
    void (*exit)(void);
} PanelStateHandlers;

extern PanelState *g_panelState_0206f9a0;
extern PanelStateHandlers g_panelStateTable_0206f8f8[];
extern void func_ov027_020b7dd4(void *animator);
extern void NNS_FndInitListWithOffset0_0204f11c(void *list);

s32 UpdatePanelState_0206cf38(void)
{
    g_panelStateTable_0206f8f8[g_panelState_0206f9a0->stateIndex].update();
    func_ov027_020b7dd4(g_panelState_0206f9a0->animator);
    NNS_FndInitListWithOffset0_0204f11c(g_panelState_0206f9a0->objectList);
    NNS_FndInitListWithOffset0_0204f11c(g_panelState_0206f9a0->entryList);
    return g_panelState_0206f9a0->result;
}
