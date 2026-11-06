#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x4];
    s8 factor;
    u8 pad_05[0x2e0 - 0x05];
    s32 velocity;
    u8 pad_2e4[0x2ec - 0x2e4];
    s8 endValue;
    s8 startValue;
    u8 pad_2ee[0x2f8 - 0x2ee];
    s32 delta;
} PanelState;

extern PanelState *gOv013PanelGlobals;

void ComputeOv013ScrollLimits(void) {
    PanelState *state = gOv013PanelGlobals;
    s32 delta = state->factor * (state->endValue - state->startValue);
    state->velocity = -delta;
    gOv013PanelGlobals->delta = delta;
}
