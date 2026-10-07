#ifndef KH_RECODED_OV002_PANEL_STATE_H
#define KH_RECODED_OV002_PANEL_STATE_H

#include "nitro/types.h"

typedef struct Ov002PanelState {
    u8 pad_000[0x10];
    u8 active : 1;
    u8 modeDirty : 1;
    u8 pad_10_bits : 6;
    u8 stateFlags;
    u8 pad_012[0x112];
    u8 messageFile[1];
} Ov002PanelState;

extern Ov002PanelState *data_ov002_0206c460;
#define gOv002PanelState data_ov002_0206c460

#endif
