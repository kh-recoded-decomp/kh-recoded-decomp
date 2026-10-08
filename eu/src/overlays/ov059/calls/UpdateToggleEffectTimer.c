#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u16 scale;
    s16 rotation;
    u8 pad_14[4];
    void *target;
    u8 pad_1c[8];
    u8 flag24;
    u8 flag25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} TrackState;

typedef struct EffectManager {
    u8 pad_0000[0x1828];
    s16 group;
    u8 pad_182a[2];
    fx32 timer;
} EffectManager;

typedef struct Actor {
    u8 pad_000[0x6cc];
    u8 attachPoint[0x928 - 0x6cc];
    u64 flags;
    u8 playerIndex;
    u8 pad_931[0x958 - 0x931];
    fx32 animStep;
    u8 pad_95c[0x9d4 - 0x95c];
    u32 toggleFlags;
} Actor;

extern EffectManager *gActorWork;
extern const VecFx32 data_0205344c;
extern BOOL func_ov021_020a9d24(u32 *flags);
extern BOOL IsBit0Set(u32 *flags);
extern void SetBit1WhenBit0Set(u32 *flags, s32 enable);
extern BOOL IsSessionFlagSet(u32 value);
extern void ResetAnimationTrackState(TrackState *state);
extern void func_ov021_020a8cc0(TrackState *state, s32 group);

void UpdateToggleEffectTimer(Actor *actor)
{
    EffectManager *manager = gActorWork;
    BOOL ready = FALSE;
    TrackState state;

    if (!func_ov021_020a9d24(&actor->toggleFlags) && (actor->flags & 0x40)) {
        ready = TRUE;
    } else if (func_ov021_020a9d24(&actor->toggleFlags) && !(actor->flags & 0x40)) {
        ready = TRUE;
    }
    if (!IsBit0Set(&actor->toggleFlags)) {
        return;
    }
    if (IsSessionFlagSet(0x3520)) {
        return;
    }
    if (!ready) {
        return;
    }
    if (manager->timer == 0) {
        ResetAnimationTrackState(&state);
        state.id = actor->playerIndex;
        state.flag25 = 2;
        state.flag24 = 0;
        state.position = data_0205344c;
        state.rotation = 0;
        state.scale = 0x1000;
        state.target = actor->attachPoint;
        state.prevIndex = state.index = -1;
        func_ov021_020a8cc0(&state, manager->group);
        manager->timer += actor->animStep;
        return;
    }
    manager->timer += actor->animStep;
    if (manager->timer < 0x3800) {
        return;
    }
    SetBit1WhenBit0Set(&actor->toggleFlags, !func_ov021_020a9d24(&actor->toggleFlags));
    manager->timer = 0;
}
