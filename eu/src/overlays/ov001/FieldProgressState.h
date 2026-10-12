#ifndef KH_RECODED_FIELD_PROGRESS_STATE_H
#define KH_RECODED_FIELD_PROGRESS_STATE_H

#include "nitro/types.h"

/* Partial view of the field context used to commit pending awards. */
typedef struct FieldProgressState {
    u8 reserved0000[0x2772];
    s16 pendingRegionProgress;
    s32 pendingExperience;
    u8 reserved2778[0x27b6 - 0x2778];
    u8 transitionFlags;
} FieldProgressState;

#endif
