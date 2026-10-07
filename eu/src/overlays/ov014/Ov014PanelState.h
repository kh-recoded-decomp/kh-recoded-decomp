#ifndef KH_RECODED_OV014_PANEL_STATE_H
#define KH_RECODED_OV014_PANEL_STATE_H

#include "nitro/types.h"

typedef struct Ov014PanelState {
    u8 pad_0000[0xcf8a];
    s8 stateIndex;
    s8 closeRequested;
    s8 step;
} Ov014PanelState;

extern Ov014PanelState *data_ov014_0206f9a0;
#define gOv014PanelState data_ov014_0206f9a0

#endif
