#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimJointState {
    u32 flags;
} AnimJointState;

typedef struct ActorAnimState {
    u8 pad_000[0x4c];
    VecFx32 rootPosition;
    u8 pad_058[0x370 - 0x58];
    u8 tracks[0x20];
    AnimJointState joints;
    u8 pad_394[0x474 - 0x394];
    VecFx32 previousRootPosition;
} ActorAnimState;

extern u16 AdvanceAnimationTracks_0202ef24(void *tracks, fx32 delta);
extern void func_01ffe1bc(AnimJointState *joints);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void ActorAnim_AdvanceAndGetRootDelta_02089118(VecFx32 *delta, ActorAnimState *state)
{
    VecFx32 rootPosition;
    VecFx32 movement;

    AdvanceAnimationTracks_0202ef24(state->tracks, 0x1000);
    state->joints.flags |= 1;
    func_01ffe1bc(&state->joints);
    rootPosition = state->rootPosition;
    VEC_Subtract_01ff9e3c(&rootPosition, &state->previousRootPosition, &movement);
    state->previousRootPosition = rootPosition;
    *delta = movement;
}
