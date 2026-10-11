#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageRecord {
    u32 type;
    u8 pad_04[8];
    u8 kind;
    u8 pad_0d[3];
    s16 actorId;
    u8 pad_12[0x5a];
    u8 group;
} StageRecord;

typedef struct StageActor {
    u8 pad_000[0x26c];
    u32 flags : 31;
    u32 flagsHigh : 1;
    u8 pad_270[0x10];
    u16 team;
    u8 pad_282[0x3e];
    VecFx32 position;
    u8 pad_2cc[0x98];
    void *lockTarget;
} StageActor;

typedef struct ProbeOwner {
    u8 pad_00[0x34];
    fx32 power;
    u8 pad_38[4];
    fx32 lift;
    u8 pad_40[6];
    u16 liftMode;
} ProbeOwner;

typedef struct ProbeInfo {
    u8 mode;
    u8 effect;
    u8 pad_02[0xa];
    fx32 values[4];
    u8 pad_1c[3];
    u8 sound;
} ProbeInfo;

typedef struct ProbeSource {
    u8 pad_00[0x10];
    ProbeOwner *owner;
    ProbeInfo *info;
    u8 pad_18[4];
    u8 shape[1];
} ProbeSource;

typedef struct ProbeResult {
    u32 flags;
    VecFx32 point;
    VecFx32 delta;
    u8 extra[4];
} ProbeResult;

typedef struct HitMessage {
    VecFx32 force;
    fx32 damage;
    u8 pad_10[0xc];
    fx32 value;
    u8 pad_20[4];
    u8 sound;
    u8 effect;
    u8 pad_26[2];
    u16 flags;
    u16 hitCount;
    u16 active;
    u16 team;
    u16 group;
    u8 pad_32[2];
    VecFx32 origin;
    u8 pad_40[8];
} HitMessage;

typedef struct GameState {
    u8 pad_0000[0x2c62];
    u8 difficulty;
} GameState;

extern GameState *data_0205fe0c;

extern void SeekFirstActiveStageEvent_0209c884(void);
extern u16 TriggerNextStageEventFromSource0_0209c8d8(void *shape, void *out, u16 *outResult);
extern StageRecord *GetStageEventRecord_0209c0ec(u32 id);
extern StageActor *GetStageActor_0209c040(int id);
extern void ComputeFlatDirectionVector_02092674(VecFx32 *from, VecFx32 *to, VecFx32 *direction);
extern fx32 GetEntryScaledValue_02096ba4(StageRecord *owner, int index);
extern void func_01ff88c4(void *dst, int value, u32 size);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void func_ov001_020958f4(StageRecord *record, HitMessage *message);

void ProbeKnockbackStageTarget_02096f38(StageRecord *self, StageActor *player, int unused, u16 valueIndex, ProbeSource *source, ProbeResult *result)
{
    ProbeOwner *owner;
    ProbeInfo *info;
    u8 *shape;
    fx32 scaled;
    fx32 power;
    fx32 lift;
    u8 hitInfo[0x18];
    VecFx32 point = {0, 0, 0};
    VecFx32 delta = {0, 0, 0};
    u16 hitFlags = 0;
    VecFx32 dir;
    HitMessage message;
    StageRecord *record;
    StageActor *actor;
    u16 id;

    if (self == NULL || player == NULL) {
        return;
    }
    if (!(player->flags & 0x2000) && self->kind != 5) {
        return;
    }
    shape = source->shape;
    owner = source->owner;
    info = source->info;
    if (shape == NULL || owner == NULL || info == NULL) {
        return;
    }
    SeekFirstActiveStageEvent_0209c884();
    while (TRUE) {
        id = TriggerNextStageEventFromSource0_0209c8d8(shape, hitInfo, NULL);
        if (id == 0) {
            break;
        }
        record = GetStageEventRecord_0209c0ec(id);
        actor = GetStageActor_0209c040(record->actorId);
        if (!(actor->flags & 0x4000) && self->kind != 5) {
            continue;
        }
        if (self == record) {
            continue;
        }
        point = actor->position;
        if (player->lockTarget == NULL) {
            ComputeFlatDirectionVector_02092674(&player->position, &point, &dir);
        }
        scaled = GetEntryScaledValue_02096ba4(self, valueIndex);
        power = owner->power;
        lift = 0;
        if (owner->liftMode == 2) {
            lift = owner->lift;
        }
        if (record->type == 5) {
            continue;
        }
        func_01ff88c4(&message, 0, sizeof(HitMessage));
        if (info->mode == 1) {
            message.flags |= 0x1000;
        }
        hitFlags = 1;
        message.active = hitFlags;
        message.team = player->team;
        message.force.x = FixedPointMultiply12(dir.x, FixedPointMultiply12(0x333, power));
        message.force.y = FixedPointMultiply12(0x333, lift);
        message.force.z = FixedPointMultiply12(dir.z, FixedPointMultiply12(0x333, power));
        message.origin = player->position;
        message.damage = scaled;
        message.group = self->group;
        message.sound = info->sound;
        message.effect = info->effect;
        message.value = info->values[data_0205fe0c->difficulty];
        message.hitCount = hitFlags;
        func_ov001_020958f4(record, &message);
        break;
    }
    if (hitFlags != 0) {
        result->flags |= hitFlags;
        result->point = point;
        result->delta = delta;
        result->extra[0] = 0;
        result->extra[1] = 0;
        result->extra[2] = 0;
        result->extra[3] = 0;
    }
}
