#ifndef KH_RECODED_EU_STAGE_OBJECT_HANDLE_H
#define KH_RECODED_EU_STAGE_OBJECT_HANDLE_H

#include "nitro/fx_types.h"
#include "nitro/types.h"

typedef struct StageObjectHandle {
    u8 pad_00[0x18];
    fx32 rotationDegrees;
    VecFx32 position;
} StageObjectHandle;

#endif
