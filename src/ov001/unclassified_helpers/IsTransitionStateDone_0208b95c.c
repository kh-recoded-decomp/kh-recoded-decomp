#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x90];
    int pendingCount;
    u8 pad_094[4];
    int mode;
    u8 pad_09c[0xa4];
    u8 tracker[0x9c];
    u16 active;
    u8 pad_1de[6];
    void *target;
} TransitionState;

extern TransitionState *data_ov001_020a04f4;
extern u32 func_0203ab80(void *tracker);

BOOL IsTransitionStateDone_0208b95c(void)
{
    TransitionState *state = data_ov001_020a04f4;

    if (state->active == 0) {
        return TRUE;
    }
    switch (state->mode) {
    case -1:
    case 0:
        return TRUE;
    case 1:
        if (func_0203ab80(state->tracker) != 0) {
            return TRUE;
        }
        break;
    default:
        if (state->target == NULL) {
            if (state->pendingCount == 0) {
                return TRUE;
            }
        } else if (func_0203ab80(state->tracker) != 0) {
            return TRUE;
        }
        break;
    }
    return FALSE;
}
