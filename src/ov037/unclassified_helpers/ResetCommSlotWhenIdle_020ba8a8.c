#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
} CommState;

extern CommState *g_commState_020bb760;
extern s32 IsScreenModeIdle_0206a814(void);

s32 ResetCommSlotWhenIdle_020ba8a8(void)
{
    CommState *state = g_commState_020bb760;

    if (IsScreenModeIdle_0206a814() == 0) {
        return -1;
    }
    state->slotIndex = -1;
    g_commState_020bb760->flags |= 0x8000;
    return 5;
}
