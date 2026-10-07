#ifndef KH_RECODED_OV082_STATE_H
#define KH_RECODED_OV082_STATE_H

#include "nitro/types.h"

typedef struct Ov082ScrollList {
    s16 count;
    s16 selectedSlot;
} Ov082ScrollList;

typedef struct Ov082State {
    Ov082ScrollList list;
} Ov082State;

extern Ov082State *gOv082State;

#endif
