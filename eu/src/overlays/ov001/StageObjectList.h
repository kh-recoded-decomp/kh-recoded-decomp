#ifndef KH_RECODED_EU_OV001_STAGE_OBJECT_LIST_H
#define KH_RECODED_EU_OV001_STAGE_OBJECT_LIST_H

#include "nitro/types.h"

typedef struct StageObjectEntry {
    u16 id;
    u16 value;
} StageObjectEntry;

typedef struct StageObjectList {
    u8 pad_00[8];
    StageObjectEntry entries[64];
    u8 count;
} StageObjectList;

extern StageObjectList *data_ov001_020a0490;
#define gStageObjectList data_ov001_020a0490

#endif
