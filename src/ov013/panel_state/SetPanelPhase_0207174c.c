#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xd258];
    s8 phase;
} PanelState;

typedef struct PanelPhase {
    void (*enter)(void);
    void (*update)(void);
    void (*exit)(void);
} PanelPhase;

extern PanelState *g_panelState_02074ce0;
extern PanelPhase data_ov013_02074b34[];

void SetPanelPhase_0207174c(s8 phase) {
    if (g_panelState_02074ce0->phase != -1) {
        data_ov013_02074b34[g_panelState_02074ce0->phase].exit();
    }
    g_panelState_02074ce0->phase = phase;
    data_ov013_02074b34[g_panelState_02074ce0->phase].enter();
}
