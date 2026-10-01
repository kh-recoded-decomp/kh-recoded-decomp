#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flag24;
    u8 flag25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} TrackState;

typedef struct Owner {
    u8 pad_0000[0x181a];
    s16 trackGroup;
} Owner;

extern void func_ov021_020a8ab4(TrackState *state);
extern void func_ov021_020a8ca0(TrackState *state, s32 group);

BOOL func_ov059_020ca1e8(void *context, void *target, void *unused, Owner *owner, VecFx32 **positionRef)
{
    TrackState state;

    func_ov021_020a8ab4(&state);
    state.id = 0;
    state.position = **positionRef;
    state.flag25 = 0;
    state.flag24 = 0;
    state.prevIndex = 0xcd;
    state.index = 1;
    func_ov021_020a8ca0(&state, owner->trackGroup);
    return TRUE;
}
