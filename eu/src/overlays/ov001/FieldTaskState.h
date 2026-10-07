#ifndef KH_RECODED_EU_OV001_FIELD_TASK_STATE_H
#define KH_RECODED_EU_OV001_FIELD_TASK_STATE_H

#include "nitro/types.h"

typedef struct FieldTaskState FieldTaskState;
typedef void (*FieldTaskUpdate)(FieldTaskState *task);

struct FieldTaskState {
    FieldTaskUpdate update;
    u32 phase;
    FieldTaskUpdate draw;
    int parameter;
    u8 active;
    u8 pad_11;
    u8 kind;
    u8 pad_13;
    u8 mode;
    u8 pad_15;
    u16 id;
};

#endif
