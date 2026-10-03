#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x1c];
    s32 result;
} CommState;

extern CommState *g_commState_020bb760;
extern s32 func_ov037_020bb4bc(void);

s32 StoreCommResultSlot_020ba8e4(void)
{
    CommState *state = g_commState_020bb760;
    s32 result = func_ov037_020bb4bc();

    if (result >= 0) {
        state->result = result;
        return 6;
    }
    return -1;
}
