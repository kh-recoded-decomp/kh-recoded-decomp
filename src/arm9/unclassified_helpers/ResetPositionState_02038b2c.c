#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackingState {
    u8 pad_00[0x20];
    VecFx32 position;
    u32 unk_2C;
    u8 pad_30[0xD8];
    u32 unk_108;
    u8 pad_10C[0x188];
    u8 unk_294;
} TrackingState;

extern VecFx32 g_zeroVec_02053438;

void ResetPositionState_02038b2c(TrackingState *state)
{
    state->unk_108 = 0;
    state->unk_2C = 0;
    state->unk_294 = 0;
    state->position = g_zeroVec_02053438;
}
