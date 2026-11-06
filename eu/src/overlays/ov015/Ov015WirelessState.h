#ifndef KH_RECODED_OV015_WIRELESS_STATE_H
#define KH_RECODED_OV015_WIRELESS_STATE_H

#include "nitro/types.h"

typedef struct Ov015WirelessState {
    s8 state;
    u8 ready;
    u8 pad_02[0x7a];
    s16 finalizeDelay;
} Ov015WirelessState;

extern Ov015WirelessState *gWirelessCardExchangeGlobals;
#define gOv015WirelessState gWirelessCardExchangeGlobals

#endif
