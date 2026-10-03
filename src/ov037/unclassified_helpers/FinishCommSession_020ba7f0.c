#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
    u8 keepAudio : 1;
} CommState;

extern CommState *g_commState_020bb760;
extern void StoreToGlobalPtr4Field28_0202a778(int value);
extern int CacheSeqArcStatus_0204e00c(int index);
extern void func_ov037_020bb3c0(void);

s32 FinishCommSession_020ba7f0(void)
{
    CommState *state = g_commState_020bb760;
    u16 flags = state->flags | 0xc;

    state->flags = flags;
    if (flags & 1) {
        state->flags &= ~1;
    }
    if (state->keepAudio) {
        StoreToGlobalPtr4Field28_0202a778(0);
        return 9;
    }
    CacheSeqArcStatus_0204e00c(2);
    func_ov037_020bb3c0();
    StoreToGlobalPtr4Field28_0202a778(0);
    g_commState_020bb760->flags |= 0x8000;
    return 3;
}
