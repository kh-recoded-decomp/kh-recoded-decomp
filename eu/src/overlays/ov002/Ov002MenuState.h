#ifndef KH_RECODED_OV002_MENU_STATE_H
#define KH_RECODED_OV002_MENU_STATE_H

#include "nitro/types.h"

typedef struct Ov002MenuState {
    u8 pad_00[2];
    s8 selection;
    u8 pad_03[0x1f];
    u8 stateFlags;
} Ov002MenuState;

extern Ov002MenuState *data_ov002_0206c464;
#define gOv002MenuState data_ov002_0206c464

#endif
