#ifndef KH_RECODED_OV031_MOVIE_STATE_H
#define KH_RECODED_OV031_MOVIE_STATE_H

#include "nitro/types.h"

typedef struct Ov031MovieRecord {
    u8 pad_00[0x14];
    u32 position;
    u8 pad_18[0x3c - 0x18];
} Ov031MovieRecord;

typedef struct Ov031MovieState {
    u8 pad_00[0x44];
    s32 recordIndex;
    u8 pad_48[8];
    Ov031MovieRecord *records;
    u8 pad_54[8];
    u16 nearestEvent;
    u8 pad_5e[0xbc - 0x5e];
    u32 frameCount;
} Ov031MovieState;

extern Ov031MovieState *data_ov031_020bc820;
#define gOv031MovieState data_ov031_020bc820

#endif
