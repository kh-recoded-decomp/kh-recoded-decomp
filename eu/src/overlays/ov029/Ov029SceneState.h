#ifndef KH_RECODED_OV029_SCENE_STATE_H
#define KH_RECODED_OV029_SCENE_STATE_H

#include "nitro/types.h"

typedef struct Ov029SceneState {
    s16 value0;
    s16 value2;
    s16 value4;
    u16 flags;
    u8 pad_08[0x0c];
    s32 timer;
} Ov029SceneState;

typedef struct Ov029SceneParams {
    u8 pad_00;
    s8 value0;
    s16 value2;
    s16 value4;
} Ov029SceneParams;

extern Ov029SceneState *data_ov029_020babc0;

#endif
