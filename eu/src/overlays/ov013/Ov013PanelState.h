#ifndef KH_RECODED_OV013_PANEL_STATE_H
#define KH_RECODED_OV013_PANEL_STATE_H

#include "nitro/types.h"

typedef struct Ov013PanelState {
    u8 pad_0000[0x2bc];
    s32 step;
    u8 pad_02c0[0xd259 - 0x2c0];
    u8 scrollStopped : 1;
    u8 scrollDown : 1;
    u8 scrollFlags : 6;
} Ov013PanelState;

extern Ov013PanelState *data_ov013_02074ce0;
#define gOv013PanelState data_ov013_02074ce0

#endif
