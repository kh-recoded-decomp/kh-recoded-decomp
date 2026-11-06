#ifndef KH_RECODED_OV028_FIELD_STATE_H
#define KH_RECODED_OV028_FIELD_STATE_H

#include "nitro/types.h"

typedef struct Ov028FieldState {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    s8 mode;
} Ov028FieldState;

extern Ov028FieldState *gOv028FieldSceneWorkStorage;
#define gOv028FieldState gOv028FieldSceneWorkStorage

#endif
