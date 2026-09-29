#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcf92];
    u8 mode;
    s8 direction;
} PanelState;

extern PanelState *g_panelState_0206f9a0;

void SetPanelDirection_0206e66c(BOOL forward)
{
    s8 direction = -1;
    if (forward) {
        direction = 1;
    }
    g_panelState_0206f9a0->direction = direction;
    g_panelState_0206f9a0->mode = 4;
}
