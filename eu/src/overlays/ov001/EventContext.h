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
    u8 pad_a4[0x14];
    u32 resourceArchiveIds[5];
} EventContext;

extern EventContext *data_ov001_020a04bc;
#define gEventContext data_ov001_020a04bc

#endif
