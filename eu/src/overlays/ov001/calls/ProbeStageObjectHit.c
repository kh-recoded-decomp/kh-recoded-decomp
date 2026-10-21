#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageRecord {
    u8 pad_00[4];
    u16 flags;
    u8 pad_06[0xc];
    u16 eventId;
} StageRecord;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    u8 sequencer[0x9c];
    u32 flags : 31;
    u32 flagsHigh : 1;
    u8 pad_270[0x1a];
    u16 flagsLow : 8;
    u16 strongRepel : 1;
    u16 flag9 : 1;
    u16 hitObjects : 4; /* stage objects already hit by the current attack, one bit each */
    u16 flagsTop : 2;
    u8 pad_28c[0x10];
    fx32 weight;
    u8 pad_2a0[0x20];
    VecFx32 position;
    u8 pad_2cc[0x9c];
    VecFx32 velocity;
} StageActor;

typedef struct ProbeOwner {
    u8 pad_00[0x24];
    u32 sticky;
    u8 pad_28[0xc];
    fx32 power;
    u8 pad_38[4];
    fx32 lift;
    u8 pad_40[6];
    u16 liftMode;
} ProbeOwner;

typedef struct ProbeInfo {
    u8 mode;
    u8 effect;
    u8 flag08;
    u8 repeatable;
    u8 blockable;
    u8 pad_05[7];
    fx32 values[4];
    u8 pad_1c[2];
    u8 flag100;
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
    u8 touched;
    u8 stuckRepel;
    u8 stuck;
} ProbeResult;

/* Hit message handed to a stage object's check callback, which fills in the reaction. */
typedef struct StageObjectHit {
    u32 flags;
    VecFx32 force;
    VecFx32 origin;
    fx32 damage;
    u32 row;
    u32 reaction;
    u32 handled;
    u32 sound;
    fx32 value;
    u32 effect;
} StageObjectHit;

enum {
    PROBE_HIT = 1,
    PROBE_REPELLED = 2,
    PROBE_REPELLED_STRONG = 4
};

typedef struct GameState {
    u8 pad_0000[0x2c62];
    u8 difficulty;
} GameState;

extern GameState *data_0205fe0c;
extern const VecFx32 gZeroVecFx32;

extern void RefreshStageEntriesIfLoaded(void);
extern u16 GetCollidingObjectCode(const void *bounds, void *hitInfo);
extern void RunOverrideTrack(void *sequencer, u16 overrideId);
extern void GetStageEntryAnchor(u32 id, VecFx32 *outPosition);
extern void ComputeFlatDirectionVector(VecFx32 *from, VecFx32 *to, VecFx32 *direction);
extern fx32 GetEntryScaledValue(StageRecord *owner, int index);
extern void func_01ff88c4(void *dst, int value, u32 size);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern u16 GetStageRowIndex(StageRecord *record);
extern int GetStageEntrySide(u32 id, StageObjectHit *hit);
extern BOOL func_ov001_0209c56c(u16 id, u16 value);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline int GetSessionMode(void)
{
    return func_ov001_02063a24() ? func_ov001_02063a38() : 0;
}

/* Send the attack's hit to the first stage object its shape touches that the player has not hit
 * yet, push the player back from it and report what happened in `result`. */
void ProbeStageObjectHit(StageRecord *self, StageActor *player, int unused, u16 valueIndex, ProbeSource *source,
                         ProbeResult *result)
{
    StageObjectHit message;
    u8 hitInfo[0x18];
    VecFx32 anchor;
    VecFx32 delta;
    VecFx32 dir;
    u8 *shape;
    ProbeOwner *owner;
    ProbeInfo *info;
    fx32 scaled;
    fx32 power;
    fx32 lift;
    int side;
    u16 index;
    u32 code;
    u8 hitFlags = 0;
    BOOL stuck = FALSE;
    BOOL touched = FALSE;
    u32 bit;
    fx32 push;

    if (self == NULL || player == NULL) {
        return;
    }
    player->hitObjects &= (u16)~(1 << 3);
    shape = source->shape;
    owner = source->owner;
    info = source->info;
    if (shape == NULL || owner == NULL || info == NULL) {
        return;
    }
    RefreshStageEntriesIfLoaded();
    for (index = hitFlags;; index++) {
        self->flags &= ~0x80;
        code = GetCollidingObjectCode(shape, hitInfo);
        if (code == 0) {
            break;
        }
        bit = 1 << index;
        if (bit & player->hitObjects) {
            continue;
        }
        touched = TRUE;
        if (player->flags & 0x400000) {
            RunOverrideTrack(player->sequencer, 8);
            break;
        }
        GetStageEntryAnchor(code, &anchor);
        ComputeFlatDirectionVector(&player->position, &anchor, &dir);
        scaled = GetEntryScaledValue(self, valueIndex);
        power = owner->power;
        if (power == 0) {
            power = FX32_ONE;
        }
        lift = 0;
        if (owner->liftMode == 2) {
            lift = owner->lift;
        }
        func_01ff88c4(&message, 0, sizeof(StageObjectHit));
        message.flags = 1;
        if (info->mode == 1) {
            message.flags |= 0x80;
        }
        if (info->flag08 == 1) {
            message.flags |= 0x8;
        }
        if (info->repeatable == 1) {
            message.flags |= 0x20;
        }
        if (info->blockable == 0) {
            message.flags |= 0x10;
        }
        if (info->flag100 == 1) {
            message.flags |= 0x100;
        }
        if (GetSessionMode() == 6) {
            scaled = 0;
        }
        message.force.x = FX_Mul(dir.x, FX_Mul(0x333, power));
        message.force.y = FX_Mul(0x333, lift);
        message.force.z = FX_Mul(dir.z, FX_Mul(0x333, power));
        message.origin = player->position;
        message.damage = scaled;
        message.sound = info->sound;
        message.effect = info->effect;
        message.value = info->values[data_0205fe0c->difficulty];
        message.row = GetStageRowIndex(self);
        if (owner->sticky == 0) {
            self->flags |= 0x80;
        }
        side = GetStageEntrySide(code, &message);
        if (side == 0) {
            continue;
        }
        if (!(message.reaction & 5) && GetSessionMode() == 6
            && func_ov001_0209c56c(self->eventId, side > 0 ? 1 : 3)) {
            hitFlags = PROBE_HIT;
            break;
        }
        player->hitObjects |= (u16)bit;
        if (info->repeatable != 0) {
            player->hitObjects &= (u16)~bit;
        }
        VEC_Subtract(&player->position, &anchor, &delta);
        if (owner->liftMode == 1 && owner->lift != 0 && player->weight != 0) {
            push = FX_Mul(player->weight, owner->lift);
            if (push < 0x19a) {
                push = 0x3000;
            }
            VEC_MultAdd(-push, &dir, &gZeroVecFx32, &player->velocity);
        }
        stuck = owner->sticky != 0;
        if (message.reaction & 1) {
            if (player->strongRepel) {
                hitFlags = PROBE_REPELLED_STRONG;
                break;
            }
            hitFlags = PROBE_REPELLED;
            break;
        }
        if (stuck || message.handled) {
            hitFlags = PROBE_HIT;
        }
        break;
    }
    if (hitFlags != 0) {
        result->flags |= hitFlags;
        result->point = anchor;
        result->delta = delta;
        result->touched = touched;
        result->stuckRepel = (hitFlags == PROBE_REPELLED && stuck) ? 1 : 0;
        result->stuck = stuck;
    }
}
