#ifndef KH_RECODED_OV040_REWARD_ANIMATION_STATE_H
#define KH_RECODED_OV040_REWARD_ANIMATION_STATE_H

#include "nitro/types.h"

typedef struct RewardAnimationGroup {
    u8 pad_00[0xc];
    u8 *animationData;
} RewardAnimationGroup;

typedef struct Ov040RewardAnimationState {
    u8 pad_00[8];
    RewardAnimationGroup *group;
} Ov040RewardAnimationState;

extern Ov040RewardAnimationState *data_ov040_020be284;
#define gOv040RewardAnimationState data_ov040_020be284

#endif
