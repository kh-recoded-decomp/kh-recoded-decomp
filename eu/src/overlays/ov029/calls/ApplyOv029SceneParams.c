#include "nitro/types.h"

typedef struct Ov029SceneParams {
    u8 pad_00;
    s8 kind;
    s16 valueA;
    s16 valueB;
} Ov029SceneParams;

typedef struct Ov029SceneState {
    s16 kind;
    s16 valueA;
    s16 valueB;
    s16 phase;
    u8 pad_08[0xc];
    int timer;
} Ov029SceneState;

extern Ov029SceneState *data_ov029_020babc0;

void ApplyOv029SceneParams(const Ov029SceneParams *params)
{
    data_ov029_020babc0->valueA = params->valueA;
    data_ov029_020babc0->valueB = params->valueB;
    data_ov029_020babc0->kind = params->kind;
    data_ov029_020babc0->phase = 3;
    data_ov029_020babc0->timer = 0;
}
