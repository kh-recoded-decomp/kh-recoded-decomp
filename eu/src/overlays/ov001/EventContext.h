#ifndef KH_RECODED_EU_OV001_EVENT_CONTEXT_H
#define KH_RECODED_EU_OV001_EVENT_CONTEXT_H

#include "nitro/types.h"

typedef struct PlayerControlState {
    u8 raw[0x20];
} PlayerControlState;

typedef struct PlayerControlSlot {
    u8 pad_00[8];
    PlayerControlState control;
} PlayerControlSlot;

typedef struct EventContext {
    u32 header;
    PlayerControlSlot players[4];
} EventContext;

extern EventContext *data_ov001_020a04bc;
#define gEventContext data_ov001_020a04bc

#endif
