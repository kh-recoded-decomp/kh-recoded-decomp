#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} HitVolume;

typedef struct {
    HitVolume volume;
    s16 *hitSlots;
    VecFx32 motion;
    fx32 scale;
    u16 angle;
    u8 pad_5a[2];
    int target;
} HitAttack;

typedef struct {
    s32 power;
    u8 pad_04[0xc];
    u8 reaction;
    u8 reactionLevel;
    u8 pad_12[0x12];
    u16 flags;
    u8 pad_26[2];
} HitOptions;

typedef struct {
    u8 pad_00[8];
    s32 kind;
    u8 pad_0c[0xc];
    u16 eventId;
    u8 pad_1a[0xd4 - 0x1a];
    s32 mode;
    u8 pad_d8[4];
} HitScan;

typedef struct {
    u8 data[0x2c];
} CylinderStorage;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 hidden;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    u8 pad_00[8];
    int soundId;
    u8 pad_0c[0x38];
    s16 groupId;
} EffectOwner;

typedef struct {
    u8 pad_000[0x9b4];
    u8 player;
} Actor;

extern const VecFx32 data_0205344c;
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void InitRecord60(HitAttack *attack);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape InitCylinderShape(CylinderStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void ZeroBytes0x28(void *obj);
extern void ZeroAndSetField0xd4(void *obj);
extern BOOL StepHitScan(int type, HitAttack *attack, HitOptions *options, HitScan *scan);
extern BOOL IsObjectType111(EffectOwner *owner);
extern void UpdateStageEventMessage(u16 eventId);

void EmitPillarHitScan(EffectOwner *owner, Actor *actor, const VecFx32 *pos)
{
    HitScan scan;
    HitAttack attack;
    HitVolume swept;
    MarkerRequest request;
    CylinderStorage cylinder;
    HitOptions options;
    VecFx32 top;
    VecFx32 bottom;
    VecFx32 axis;
    VecFx32 diff;
    CollisionShape shapeResult;
    HitScan *hit;

    ResetAnimationTrackState(&request);
    request.id = actor->player;
    request.layer = 0;
    request.hidden = 0;
    request.position = *pos;
    request.soundId = owner->soundId;
    request.delay = 1;
    if (func_ov021_020a8cc0(&request, owner->groupId) == -1) {
        return;
    }
    bottom = *pos;
    top = bottom;
    top.y += 0x6000;
    bottom.y -= 0x800;
    InitRecord60(&attack);
    VEC_Subtract(&bottom, &top, &diff);
    axis = diff;
    shapeResult = InitCylinderShape(&cylinder, &top, &bottom, &axis, func_01ffaff4(&axis, &axis), 0x1000);
    swept.shape = shapeResult;
    swept.delta = data_0205344c;
    OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
    attack.volume = swept;
    ZeroBytes0x28(&options);
    options.power = IsObjectType111(owner) ? 0x902 : 0x600;
    options.reaction = 1;
    options.flags |= 0x80;
    options.flags |= 0x800;
    options.reactionLevel = 3;
    options.flags |= 0x400;
    hit = &scan;
    ZeroAndSetField0xd4(hit);
    hit->mode = 3;
    while (StepHitScan(actor->player, &attack, &options, hit)) {
        if (hit->kind == 4) {
            UpdateStageEventMessage(hit->eventId);
        }
    }
}
