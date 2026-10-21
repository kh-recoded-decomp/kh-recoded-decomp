#ifndef KH_RECODED_FIELD_PROGRESS_STATE_H
#define KH_RECODED_FIELD_PROGRESS_STATE_H

#include "nitro/types.h"

/* Partial view of the field context used to commit pending awards. */
typedef struct FieldProgressState {
    u8 reserved0000[0x214];
    u32 sceneFlags;
    u8 reserved0218[0x2772 - 0x218];
    s16 pendingRegionProgress;
    s32 pendingExperience;
    u8 reserved2778[0x27b6 - 0x2778];
    u8 transitionFlags;
} FieldProgressState;

#endif
