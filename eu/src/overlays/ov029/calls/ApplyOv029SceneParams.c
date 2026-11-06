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

extern Ov029SceneState *gOv029SceneWorkStorage;

void ApplyOv029SceneParams(const Ov029SceneParams *params)
{
    gOv029SceneWorkStorage->valueA = params->valueA;
    gOv029SceneWorkStorage->valueB = params->valueB;
    gOv029SceneWorkStorage->kind = params->kind;
    gOv029SceneWorkStorage->phase = 3;
    gOv029SceneWorkStorage->timer = 0;
}
