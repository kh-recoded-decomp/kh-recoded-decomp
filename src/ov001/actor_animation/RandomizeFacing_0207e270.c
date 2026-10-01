#include "nitro/types.h"

typedef struct FacingState {
    u8 pad_00[0x24];
    s16 angle;
    s16 turnTarget;
    s16 turnSpeed;
} FacingState;

extern u32 func_0202a9d0(u32 range);
extern void func_ov001_0207e1c0(FacingState *state);

void RandomizeFacing_0207e270(FacingState *state, BOOL apply)
{
    state->angle = (int)(func_0202a9d0(4) << 16) / 4;
    state->turnTarget = -1;
    state->turnSpeed = 0x400;
    if (apply) {
        func_ov001_0207e1c0(state);
    }
}
