#ifndef KH_RECODED_OV036_TEXT_WINDOW_STATE_H
#define KH_RECODED_OV036_TEXT_WINDOW_STATE_H

#include "nitro/types.h"

typedef struct Ov036TextWindowState {
    u8 pad_0000[0x68a0];
    s32 choiceResult;
} Ov036TextWindowState;

extern Ov036TextWindowState *gTextWindowResourceTable;

#endif
