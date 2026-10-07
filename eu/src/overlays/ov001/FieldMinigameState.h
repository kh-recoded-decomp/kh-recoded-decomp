#ifndef KH_RECODED_EU_OV001_FIELD_MINIGAME_STATE_H
#define KH_RECODED_EU_OV001_FIELD_MINIGAME_STATE_H

#include "nitro/types.h"

typedef struct FieldMinigameState {
    int mode;
    u8 pad_04[0x1c];
    int active;
    u8 pad_24[0x88];
    int score;
    int level;
} FieldMinigameState;

extern FieldMinigameState *data_ov001_020a04f4;
#define gFieldMinigameState data_ov001_020a04f4

#endif
