#include "nitro/types.h"

typedef struct Panel Panel;
typedef void (*PanelStateFunc)(Panel *panel);

typedef struct PanelStateHandlers {
    PanelStateFunc first;
    PanelStateFunc second;
    PanelStateFunc third;
} PanelStateHandlers;

struct Panel {
    u8 pad_0[0x24];
    s32 stateTimer;
    u8 pad_28[0x2c - 0x28];
    s32 state;
    s32 nextState;
    u8 pad_34[0x3c - 0x34];
    s32 frame;
    s32 fadeInFrames;
    s32 fadeOutFrames;
};

extern PanelStateHandlers gPanelStateHandlers[];
extern PanelStateHandlers gPanelPhaseHandlers[];

int SwitchPanelState(Panel *panel)
{
    int phase = 2;

    gPanelStateHandlers[panel->state].first(panel);
    panel->state = panel->nextState;
    gPanelPhaseHandlers[panel->state].first(panel);
    panel->stateTimer = 0;
    panel->frame = 0;
    if (panel->fadeOutFrames <= 0) {
        phase = 3;
    }
    return phase;
}
