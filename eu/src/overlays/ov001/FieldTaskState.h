#ifndef KH_RECODED_EU_OV001_FIELD_TASK_STATE_H
#define KH_RECODED_EU_OV001_FIELD_TASK_STATE_H

#include "nitro/types.h"

typedef struct FieldTaskState FieldTaskState;
typedef void (*FieldTaskUpdate)(FieldTaskState *task);

struct FieldTaskState {
    FieldTaskUpdate update;
    u32 phase;
    void *release;
    u32 parameter;
    u8 active;
};

#endif
