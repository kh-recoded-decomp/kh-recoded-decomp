#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xCFE0];
    s32 phase;
    s32 step;
    s32 phaseTimer;
} Ov101State;

extern Ov101State *data_ov101_020c5920;

void SetStatePhase(s32 phase)
{
    Ov101State *state = data_ov101_020c5920;

    state->phase = phase;
    state->step = 0;
    state->phaseTimer = 0;
}
