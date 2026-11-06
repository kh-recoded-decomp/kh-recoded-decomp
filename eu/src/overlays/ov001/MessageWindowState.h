#ifndef KH_RECODED_EU_OV001_MESSAGE_WINDOW_STATE_H
#define KH_RECODED_EU_OV001_MESSAGE_WINDOW_STATE_H

#include "nitro/types.h"

typedef struct MessageWindowState {
    u8 pad_00[0x7e];
    u16 result;
} MessageWindowState;

extern MessageWindowState *gMessageWindowWork;
#define gMessageWindowState gMessageWindowWork

#endif
