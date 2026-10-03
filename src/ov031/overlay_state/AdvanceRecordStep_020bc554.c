#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    s32 stepIndex;
    s32 recordIndex;
    u8 pad_48[0x4];
    u32 *stepCodes;
    u8 pad_50[0x4];
    u8 stepCount;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void ReportContextError_020bc524(u32 code);
extern void func_ov031_020bb5d8(void);

void AdvanceRecordStep_020bc554(void)
{
    OverlayState *state;
    s32 index;

    g_activeState_020bc800->stepIndex++;
    state = g_activeState_020bc800;
    index = state->stepIndex;
    if (index < state->stepCount) {
        ReportContextError_020bc524(state->stepCodes[index]);
    } else if (state->recordIndex != -1) {
        func_ov031_020bb5d8();
    } else {
        state->stepIndex = index - 1;
    }
}
