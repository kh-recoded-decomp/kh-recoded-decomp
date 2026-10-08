#include "nitro/types.h"

typedef struct ResumeModeState {
    u8 pad_00[6];
    u16 flags;
} ResumeModeState;

extern ResumeModeState *data_ov033_020baae0;

u32 ClearResumeModeReadyFlag(void)
{
    ResumeModeState *state = data_ov033_020baae0;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
