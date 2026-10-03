#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    s16 scale;
    u16 angle;
    s32 rate;
    void *target;
    u8 pad_1c[8];
    u8 mode;
    u8 loop;
    s16 priority;
    s16 index;
} TrackState;

typedef struct EffectParams {
    u8 pad_00[4];
    s16 frame;
} EffectParams;

typedef struct EffectContext {
    u8 pad_000[0x6cc];
    u8 target[0x2e8];
    u8 effectId;
    u8 pad_9b5[0x61b];
    EffectParams *params;
} EffectContext;

typedef struct GroupMember {
    u8 pad_00[0xb8];
    int frame;
} GroupMember;

typedef struct EffectOwner {
    u8 pad_00[0x20];
    EffectContext *context;
    u8 pad_24[0xc];
    s16 mainGroup;
    s16 subGroup;
} EffectOwner;

extern void func_ov021_020a8ab4(TrackState *state);
extern int func_ov021_020a8ca0(TrackState *request, int groupId);
extern void StopAndClearSoundEmitter_020a8e14(int group, int member);
extern GroupMember *GetGroupMemberData_020a8eec(int group, int member);
extern BOOL IsGroupMemberActive_020a8d1c(int group, int member);

void RestartObjectEffect_020a0eec(EffectOwner *owner)
{
    EffectContext *context = owner->context;
    TrackState request;

    func_ov021_020a8ab4(&request);
    request.id = context->effectId;
    request.loop = 2;
    request.priority = 2;
    request.mode = 2;
    request.target = context->target;
    StopAndClearSoundEmitter_020a8e14(owner->mainGroup, 0);
    func_ov021_020a8ca0(&request, owner->mainGroup);
    GetGroupMemberData_020a8eec(owner->mainGroup, 0)->frame = context->params->frame;
    if (IsGroupMemberActive_020a8d1c(owner->subGroup, 0)) {
        StopAndClearSoundEmitter_020a8e14(owner->subGroup, 0);
    }
}
