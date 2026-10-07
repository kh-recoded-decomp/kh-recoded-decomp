#ifndef KH_RECODED_OV028_FIELD_STATE_H
#define KH_RECODED_OV028_FIELD_STATE_H

#include "nitro/types.h"

typedef struct Ov028FieldState {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
} Ov028FieldState;

extern Ov028FieldState *data_ov028_020bb3a0;
#define gOv028FieldState data_ov028_020bb3a0

#endif
