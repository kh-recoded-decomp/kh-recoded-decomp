#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    s32 position;
    u8 pad_2c[0x4];
    s32 target;
    s32 step;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

s32 GetSeekStep_020bc018(void)
{
    OverlayState *state = g_activeState_020bc800;
    s32 diff = state->target - state->position;
    s32 sign;

    if (diff == 0) {
        sign = 0;
    } else if (diff > 0) {
        sign = 1;
    } else {
        sign = -1;
    }
    return state->step * sign;
}
