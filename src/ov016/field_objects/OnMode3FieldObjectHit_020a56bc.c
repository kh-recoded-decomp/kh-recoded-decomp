#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 locked;
    u8 variant;
} HitState;

typedef struct {
    u8 pad_000[0x194];
    HitState state;
} HitOwner;

typedef struct {
    HitOwner **owner;
    int kind;
} HitSource;

typedef struct {
    HitSource *source;
    int type;
} HitInfo;

typedef struct {
    u8 pad_00[0xb4];
    s16 groupId;
} FieldOwner;

typedef struct {
    u8 pad_00[4];
    FieldOwner *owner;
    u8 pad_08[0x38 - 0x08];
    VecFx32 position;
    u8 pad_44[0x77 - 0x44];
    u8 mode;
    u8 pad_78[0xc8 - 0x78];
    int soundId;
    VecFx32 velocity;
    u32 pushed : 1;
    u32 pushRest : 31;
} FieldObject;

typedef struct {
    FieldObject *obj;
    int arg1;
    int arg2;
    int arg3;
} HitContext;

typedef struct {
    u8 pad_000[4];
    u16 strength;
} PushConfig;

typedef struct {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_c8[0x1d4 - 0xc8];
    PushConfig *config;
} PlayerEntry;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x24 - 0x10];
    u8 flagA;
    u8 flagB;
    u8 pad_26[0x2c - 0x26];
} TrackState;

extern BOOL IsMovingAgainstDirection_02086618(FieldObject *object, int entryIndex, const VecFx32 *direction);
extern PlayerEntry *GetBoundedEntryField_0206db5c(int index);
extern BOOL SendPushMessage_02086534(FieldObject *source, int index, VecFx32 *velocity, s32 strength);
extern void func_ov021_020a8ab4(TrackState *state);
extern int func_ov021_020a8ca0(TrackState *request, int groupId);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern void OnFieldUnitPushedUp_020a566c(void *self, u16 other, const VecFx32 *push, HitInfo *hit, int context, int arg1, int arg2, int arg3);

void OnMode3FieldObjectHit_020a56bc(void *self, u16 other, const VecFx32 *push, HitInfo *hit, int context, int arg1, int arg2, int arg3)
{
    HitState *state;
    PlayerEntry *player;
    VecFx32 *playerPos;
    TrackState track;
    FieldObject *obj = (FieldObject *)context;

    if (obj->mode == 3 && obj->soundId == 0 && hit != NULL && hit->type == 2 && hit->source->kind == 0) {
        state = &(*hit->source->owner)->state;
        if (state->locked == 0 && state->variant == 0 && IsMovingAgainstDirection_02086618(obj, state->variant, push)) {
            obj->pushed = 1;
            obj->velocity = *push;
            player = GetBoundedEntryField_0206db5c(0);
            playerPos = &player->position;
            if (SendPushMessage_02086534(obj, 0, &obj->velocity, (player->config->strength << 12) / 10)) {
                func_ov021_020a8ab4(&track);
                track.flagB = 0;
                track.position = *playerPos;
                track.id = 0;
                track.flagA = 0;
                track.position.y += 0xc00;
                func_ov021_020a8ca0(&track, obj->owner->groupId);
                SpawnSoundSlot_0204da8c(0, 0x36, &obj->position, 0);
            }
            obj->soundId = 0x1333;
        }
    }
    OnFieldUnitPushedUp_020a566c(self, other, push, hit, context, arg1, arg2, arg3);
}
