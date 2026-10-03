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

typedef struct EventTargetInfo {
    u16 id;
    u16 flags;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct EffectContext {
    u8 pad_000[0x9b4];
    u8 effectId;
} EffectContext;

typedef struct GroupMember {
    u8 pad_00[0xa4];
    VecFx32 position;
} GroupMember;

typedef struct EffectOwner {
    u8 pad_00[0xc];
    void *model;
    u8 pad_10[8];
    int targetId;
    u8 pad_1c[4];
    EffectContext *context;
    u8 pad_24[0x12];
    s16 hitGroup;
} EffectOwner;

extern void func_ov021_020a8ab4(TrackState *state);
extern int func_ov021_020a8ca0(TrackState *request, int groupId);
extern void StopAndClearSoundEmitter_020a8e14(int group, int member);
extern GroupMember *GetGroupMemberData_020a8eec(int group, int member);
extern BOOL GetStageEventTargetInfo_02087960(u16 id, EventTargetInfo *info);

void SpawnEffectAtTarget_020a1028(EffectOwner *owner)
{
    EffectContext *context = owner->context;
    TrackState request;
    EventTargetInfo info;
    VecFx32 position;

    if (owner->model != NULL) {
        position = GetGroupMemberData_020a8eec(owner->hitGroup, 0)->position;
        StopAndClearSoundEmitter_020a8e14(owner->hitGroup, 0);
        if (owner->targetId >= 0 && GetStageEventTargetInfo_02087960(owner->targetId, &info)) {
            position = info.position;
            position.y += 0x800;
        }
        func_ov021_020a8ab4(&request);
        request.id = context->effectId;
        request.loop = 0;
        request.mode = 2;
        request.position = position;
        func_ov021_020a8ca0(&request, owner->hitGroup);
    }
}
