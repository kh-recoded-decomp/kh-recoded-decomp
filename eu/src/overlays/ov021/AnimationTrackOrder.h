#ifndef RECODED_OV021_ANIMATION_TRACK_ORDER_H
#define RECODED_OV021_ANIMATION_TRACK_ORDER_H

#include "nitro/types.h"

typedef struct AnimationTrackOrder {
    u32 tracks[5];
} AnimationTrackOrder;

typedef char AnimationTrackOrderSize[sizeof(AnimationTrackOrder) == 0x14 ? 1 : -1];

extern const AnimationTrackOrder kPrimaryModelTrackOrder;
extern const AnimationTrackOrder kSecondaryModelTrackOrder;

#endif
