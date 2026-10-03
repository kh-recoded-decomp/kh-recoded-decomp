#include "nitro/types.h"

typedef struct PanelMode {
    void (*enter)(void);
    void (*update)(void);
    void (*exit)(void);
    void (*draw)(void);
} PanelMode;

typedef struct PanelState {
    u8 pad_00[0x8];
    int mode;
    int entryMode;
    u8 unk_10_b0 : 1;
    u8 modeDirty : 1;
    u8 unk_10_b2 : 6;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern PanelMode data_ov002_0206c2ec[];

void SwitchPanelMode_02062cb8(int mode)
{
    PanelState *state = g_panelState_0206c460;
    state->modeDirty = 0;
    if (state->mode != -1) {
        data_ov002_0206c2ec[state->mode].exit();
    }
    state->mode = mode;
    data_ov002_0206c2ec[mode].enter();
}
