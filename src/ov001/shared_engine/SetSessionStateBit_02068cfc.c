#include "nitro/types.h"

typedef struct SessionState {
    u8 pad_00[0x20];
    u16 flags;
} SessionState;

extern SessionState *data_ov001_020a0474;

void SetSessionStateBit_02068cfc(BOOL enable, u32 bit)
{
    SessionState *state = data_ov001_020a0474;

    if (enable) {
        state->flags |= (u16)(1 << bit);
        return;
    }
    state->flags &= (u16)~(1 << bit);
}
