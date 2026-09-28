#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xCFCC];
    s32 phase;
    s32 step;
    s32 unk_CFD4;
} Ov101State;

extern Ov101State *g_ov101State_020c4d20;

void SetStatePhase_020c0c18(s32 phase)
{
    Ov101State *state = g_ov101State_020c4d20;

    state->phase = phase;
    state->step = 0;
    state->unk_CFD4 = 0;
}
