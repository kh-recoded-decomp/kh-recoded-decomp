#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2e[2];
    s32 result;
} ScriptContext;

typedef struct {
    u16 flags;
    s16 frames[5];
    void *anims[5];
} AnimTrackSet;

typedef struct {
    u32 unk_00;
    AnimTrackSet tracks;
} ActorModel;

typedef struct {
    u8 pad_00[0x10];
    ActorModel model;
} PlayerActor;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56a4;
extern fx32 Anim_GetFrame_0202f4a0(AnimTrackSet *tracks, u16 index);
extern fx32 func_0202f4b8(AnimTrackSet *tracks, u16 index);
extern fx32 ApplyActorScaleFactors_02091818(PlayerActor *actor);

int ScriptOp_IsPlayerAnimDone_020b0be8(ScriptContext *context)
{
    PlayerActor *player = data_ov021_020b56a4.player;
    ActorModel *model;
    fx32 frame;
    fx32 length;

    if (player == NULL) {
        return 0;
    }
    model = &player->model;
    context->resultType = 1;
    context->result = 0;
    frame = Anim_GetFrame_0202f4a0(&model->tracks, 0);
    length = func_0202f4b8(&model->tracks, 0);
    if (model->tracks.frames[0] < 0) {
        context->result = 1;
    }
    if (frame >= length - ApplyActorScaleFactors_02091818(player)) {
        context->result = 1;
    }
    return 0;
}
