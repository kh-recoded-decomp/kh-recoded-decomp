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
    u8 pad_04[8];
    s32 reach;
    u8 pad_10[2];
    u8 reaction;
    u8 pad_13[0x0d];
    s32 knockback;
    u16 hitAll : 1;
    u16 flag1 : 1;
    u16 flag2 : 1;
    u16 flag3 : 7;
    u16 flag10 : 1;
    u16 flag11 : 1;
    u16 flag12 : 1;
    u8 pad_26[2];
} HitOptions;

typedef struct {
    u8 data[0xdc];
} HitScan;

typedef struct {
    u8 data[0x2c];
} CylinderStorage;

typedef struct {
    u8 pad_000[4];
    s32 timer;
    VecFx32 anchor;
    u8 pad_014[0x778 - 0x14];
    s16 slotGroups[3][4];
    s16 slots[4];
} OverlayState;

typedef struct {
    u8 pad_000[0x7c];
    u16 angle;
    u8 pad_07e[0xa4 - 0x7e];
    VecFx32 position;
    u8 pad_0b0[0x134 - 0xb0];
} HazardEntry;

extern OverlayState data_ov058_020d8a24;
extern HazardEntry data_ov058_020d8ccc[];

extern void InitRecord60_020ac0b8(HitAttack *attack);
extern void RotateOffsetAroundY_020a9160(VecFx32 *out, const VecFx32 *origin, int angle, const VecFx32 *offset);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape InitCylinderShape_0203aeac(CylinderStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void func_0203ad14(HitVolume *volume, int *bounds, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void ZeroBytes0x28_020ac0f8(void *obj);
extern void ZeroAndSetField0xd4_020ac150(void *obj);
extern BOOL StepHitScan_020ac164(int type, HitAttack *attack, HitOptions *options, HitScan *scan);

void PulseHazardHitScans_020d7a44(int index)
{
    HitAttack attack;
    HitScan scan;
    HitVolume swept;
    HitVolume volume;
    HitOptions options;
    int bounds[4];
    VecFx32 base;
    VecFx32 tip;
    CylinderStorage cylinder;
    VecFx32 center;
    VecFx32 axis;
    VecFx32 diff;
    CollisionShape shapeResult;
    OverlayState *state = &data_ov058_020d8a24;
    HazardEntry *entry = &data_ov058_020d8ccc[index];
    int i;

    if ((state->timer + index * 0x1000) % 0x8000 != 0) {
        return;
    }
    InitRecord60_020ac0b8(&attack);
    base = entry->position;
    tip.x = 0;
    tip.y = 0;
    tip.z = 0x7000;
    RotateOffsetAroundY_020a9160(&tip, &base, entry->angle, &tip);
    VEC_Subtract_01ff9e3c(&tip, &base, &diff);
    axis = diff;
    shapeResult = InitCylinderShape_0203aeac(&cylinder, &base, &tip, &axis, func_01ffaff4(&axis, &axis), 0x14cd);
    swept.shape = shapeResult;
    swept.delta = attack.motion;
    OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
    attack.volume = swept;
    attack.hitSlots = state->slotGroups[index];
    for (i = 0; i < 4; i++) {
        attack.hitSlots[i] = -1;
    }
    ZeroBytes0x28_020ac0f8(&options);
    options.power = 0x4cd;
    options.reaction = 9;
    options.reach = 0x64000;
    options.knockback = 0;
    options.hitAll = 1;
    options.flag2 = 1;
    options.flag12 = 1;
    options.flag10 = 1;
    ZeroAndSetField0xd4_020ac150(&scan);
    while (StepHitScan_020ac164(0, &attack, &options, &scan)) {
    }

    InitRecord60_020ac0b8(&attack);
    center = state->anchor;
    center.y += 0x1000;
    func_0203ad14(&volume, bounds, &center, 0x1400);
    volume.delta = attack.motion;
    OffsetBoxByDelta_0203ac70(&volume.shape.bounds, &volume.sweptBounds, &volume.delta);
    attack.volume = volume;
    attack.hitSlots = state->slots;
    ZeroBytes0x28_020ac0f8(&options);
    options.power = 0x4cd;
    options.knockback = 0;
    options.hitAll = 1;
    options.flag2 = 1;
    options.flag12 = 1;
    ZeroAndSetField0xd4_020ac150(&scan);
    while (StepHitScan_020ac164(0, &attack, &options, &scan)) {
    }
}
