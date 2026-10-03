#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TurnActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
} TurnActor;

typedef struct TurnObject {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[0x13];
    u16 targetAngle;
    u8 pad_4e[0xa];
    u8 state;
    s8 flags;
    s8 animIndex;
    s8 cooldown;
    fx32 turnStep;
    fx32 turnAngle;
} TurnObject;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 unused0 : 6;
    u32 locked : 1;
    u32 unused7 : 5;
    u32 busy : 1;
    u32 unused13 : 19;
} FieldState;

extern FieldState *data_ov001_020a0460;
extern BOOL FieldObject_GetSavedValue_0207f9a8(TurnObject *object);
extern BOOL func_ov001_02063838(void);
extern BOOL func_ov001_02064490(void);
extern BOOL IsLeadActorWithinRadius_02080e30(TurnObject *object);
extern void ConfigureChannelSlot_0206ca68(int channel, int mode, int value);
extern TurnActor *func_02036240(u32 id);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern fx32 func_0202f4b8(void *anim, int track);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern BOOL BuildSlotMask_0202f034(void *anim, fx32 frame);

int UpdateTurningFieldObject_020810c8(TurnObject *object)
{
    TurnActor *actor;
    int delta;
    u32 angle;

    if (!(object->flags & 0x80) && FieldObject_GetSavedValue_0207f9a8(object)) {
        return 0;
    }
    if (func_ov001_02063838()) {
        object->cooldown = 5;
    } else if (object->cooldown > 0) {
        object->cooldown = object->cooldown - 1;
    }
    if (object->cooldown == 0 && !data_ov001_020a0460->locked && object->state != 1
        && !func_ov001_02064490() && !data_ov001_020a0460->busy
        && IsLeadActorWithinRadius_02080e30(object)) {
        ConfigureChannelSlot_0206ca68(0, 1, 0);
    }
    if (object->state == 0 && object->animIndex > 0) {
        actor = func_02036240(object->actorId);
        RebindAnimTracks_020809d0(&actor->animFlags, object->animIndex, 0);
        delta = object->targetAngle - actor->angle;
        if (delta > 0x8000) {
            delta -= 0x10000;
        } else if (delta < -0x8000) {
            delta += 0x10000;
        }
        object->turnStep = FX_Div_01ff9c84(delta << 12, func_0202f4b8(&actor->animFlags, 0));
        object->turnAngle = actor->angle << 12;
        object->state = 3;
    }
    if (object->state == 3) {
        actor = func_02036240(object->actorId);
        object->turnAngle += object->turnStep;
        if (BuildSlotMask_0202f034(&actor->animFlags, 0x1000)) {
            object->turnAngle = object->targetAngle << 12;
            object->animIndex = -1;
            object->state = 0;
            RebindAnimTracks_020809d0(&actor->animFlags, 0, 0);
        }
        angle = (u32)(object->turnAngle << 4) >> 16;
        if (!(actor->flags & 0x20)) {
            actor->angle = angle;
            actor->animFlags |= 0x20;
        }
    }
    return 0;
}
