#ifndef KH_RECODED_OV015_WIRELESS_STATE_H
#define KH_RECODED_OV015_WIRELESS_STATE_H

#include "nitro/types.h"

typedef struct Ov015WirelessState {
    s8 state;
    u8 ready;
    u8 pad_02[0x7a];
    s16 finalizeDelay;
} Ov015WirelessState;

extern Ov015WirelessState *data_ov015_0207e964;
#define gOv015WirelessState data_ov015_0207e964

#endif
