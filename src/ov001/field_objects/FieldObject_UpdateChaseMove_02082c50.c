#pragma thumb on
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Vec2 {
    fx32 x;
    fx32 z;
} Vec2;

typedef struct Box {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CollisionShape {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct ShapeStorage {
    u32 words[11];
} ShapeStorage;

typedef struct QueryWorkspace {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct QueryCallback {
    void *func;
    void *context;
} QueryCallback;

typedef struct QueryFilter {
    s32 value;
    s32 mask;
} QueryFilter;

typedef struct CollisionQuery {
    u8 pad_00[0x48];
    QueryCallback filter;
    QueryCallback contact;
    u8 pad_58[8];
} CollisionQuery;

typedef struct CollisionHit {
    u8 pad_00[0x2c];
    VecFx32 normal;
    VecFx32 position;
} CollisionHit;

typedef struct FieldObjectBody {
    u8 pad_000[0x10];
    u8 actor[0x130];
    SweptShape shape;
} FieldObjectBody;

typedef struct ModelActor {
    u8 pad_00[0x7c];
    void *model;
} ModelActor;

typedef struct FieldObject {
    u8 pad_00[0xc];
    FieldObjectBody *body;
    u8 pad_10[0x38 - 0x10];
    u8 actorId;
    u8 pad_39[0x40 - 0x39];
    VecFx32 position;
    u16 rotation;
    u8 pad_4e[0x5c - 0x4e];
    Vec2 velocity;
    s16 angle;
    s8 direction;
    u8 touched : 1;
    u8 blocked : 1;
    u8 alpha : 6;
    fx32 fadeTimer;
    VecFx32 push;
} FieldObject;

extern const VecFx32 data_02053438;
extern const s16 data_0205356c[];

extern void func_ov001_02063d4c(int mode, fx32 value);
extern int func_ov001_02063a4c(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern ModelActor *func_02036240(u32 actorId);
extern void Model_SetAllMaterialAlpha_0201a900(void *model, u32 alpha);
extern void Vec2Sub_0204a318(const Vec2 *a, const Vec2 *b, Vec2 *out);
extern void NormalizeVec2Fx32_0204a4a8(Vec2 *out, const Vec2 *vec, fx32 *outLength);
extern fx32 DotFx32Xy_0204a390(const Vec2 *a, const Vec2 *b);
extern u16 AngleBetweenXy_0204a508(const Vec2 *a, const Vec2 *b);
extern fx32 NormalizeXy_0204a3e4(Vec2 *xy);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *out);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern CollisionHit *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void func_0204b0ac(VecFx32 *vec, const VecFx32 *ref, int amount);
extern void FieldObject_SetSavedValue_0207f9c8(FieldObject *object, u32 value);
extern void SetSlotLayoutHighlight_0207d45c(int highlight);
extern void FallCylinderObject_020831a8(FieldObject *object);
extern void FieldObject_SyncActorTransform_0208352c(FieldObject *object);
extern int CheckFacingAway_0208350c();
extern BOOL CanTriggerOnContact_02083320();
extern BOOL FieldObject_HandlePush_0208334c();

static inline Vec2 MakeVec2(fx32 x, fx32 z)
{
    Vec2 result;
    result.x = x;
    result.z = z;
    return result;
}

static inline Vec2 SubVec2(const Vec2 *a, const Vec2 *b)
{
    Vec2 result;
    Vec2Sub_0204a318(a, b, &result);
    return result;
}

static inline Vec2 NormalizeVec2(Vec2 vec, fx32 *length)
{
    Vec2 result;
    NormalizeVec2Fx32_0204a4a8(&result, &vec, length);
    return result;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline VecFx32 SubVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract_01ff9e3c(a, b, &result);
    return result;
}

static inline VecFx32 MultAddVec(fx32 scale, VecFx32 vec, const VecFx32 *add)
{
    VecFx32 result;
    VEC_MultAdd_01ffa09c(scale, &vec, add, &result);
    return result;
}

static inline void SetShapeDelta(SweptShape *shape, const VecFx32 *delta)
{
    shape->delta = *delta;
    OffsetBoxByDelta_0203ac70(&shape->shape.bounds, &shape->sweptBounds, &shape->delta);
}

static inline QueryFilter MakeFilter(s32 value, s32 mask)
{
    QueryFilter filter;
    filter.value = value;
    filter.mask = mask;
    return filter;
}

static inline QueryCallback MakeCallback(void *func, void *context)
{
    QueryCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

static inline int Sign(int value)
{
    if (value == 0) {
        return 0;
    }
    if (value > 0) {
        return 1;
    }
    return -1;
}

int FieldObject_UpdateChaseMove_02082c50(FieldObject *object)
{
    SweptShape shapeCopy;
    QueryWorkspace workspace;
    CollisionQuery sweep;
    QueryWorkspace groundWorkspace;
    CollisionQuery groundSweep;
    CollisionQuery query;
    CollisionQuery groundQuery;
    ShapeStorage storage;
    VecFx32 offset;
    VecFx32 motion;
    VecFx32 normalDelta;
    VecFx32 turned;
    VecFx32 step;
    VecFx32 offsetRaw;
    VecFx32 stepTmp;
    VecFx32 moved;
    VecFx32 normalDeltaRaw;
    Vec2 forward;
    Vec2 right;
    fx32 distance;
    Vec2 dir;
    QueryFilter filter;
    BOOL hitWall;
    Vec2 heading;
    QueryFilter groundFilter;
    Vec2 toTarget;
    Vec2 objectXz;
    Vec2 targetXz;
    Vec2 forwardTmp;
    Vec2 rightTmp;
    Vec2 objectTmp;
    Vec2 targetTmp;
    VecFx32 *target;
    BOOL landed;
    CollisionHit *hit;
    int idx;
    BOOL tooClose;

    func_ov001_02063d4c(6, 0x1000);
    if (object->alpha != 0x10) {
        object->fadeTimer += 0x1000;
        if (object->fadeTimer >= 0xf000) {
            object->fadeTimer = 0xf000;
            object->alpha = 0x10;
        } else {
            object->alpha = (u8)((FX_Div_01ff9c84(object->fadeTimer, 0xf000) << 4) >> 12);
        }
        Model_SetAllMaterialAlpha_0201a900(func_02036240(object->actorId)->model, object->alpha);
    }
    if (func_ov001_02063a4c() != 4) {
        goto done;
    }
    idx = (u16)object->angle >> 4;
    tooClose = FALSE;
    forwardTmp.x = data_0205356c[(0x400 - idx) & 0xfff];
    forwardTmp.z = data_0205356c[idx];
    forward = forwardTmp;
    rightTmp.x = data_0205356c[idx];
    rightTmp.z = -data_0205356c[(0x400 - idx) & 0xfff];
    right = rightTmp;
    target = func_ov001_0206dc4c(0);
    targetTmp.x = target->x;
    targetTmp.z = target->z;
    targetXz = targetTmp;
    objectTmp.x = object->position.x;
    objectTmp.z = object->position.z;
    objectXz = objectTmp;
    toTarget = NormalizeVec2(SubVec2(&targetXz, &objectXz), &distance);
    dir.x = toTarget.x;
    dir.z = toTarget.z;
    if (distance < FixedPointMultiply12(0xccd, 0x666)) {
        tooClose = TRUE;
    }
    if (!tooClose && (object->velocity.x != 0 || object->velocity.z != 0)) {
        shapeCopy = object->body->shape;
        storage = *(ShapeStorage *)object->body->shape.shape.data;
        filter = MakeFilter(0, 0x15);
        CollisionQuery_Init_02034c74(&query, 0, object->body->actor, 2, 0, 1, &shapeCopy, &workspace, &filter);
        sweep = query;
        hitWall = FALSE;
        VEC_Subtract_01ff9e3c(target, &object->position, &offsetRaw);
        offset = offsetRaw;
        offset.y = 0;
        shapeCopy.shape.data = &storage;
        SetShapeDelta(&shapeCopy, &offset);
        sweep.contact = MakeCallback(CheckFacingAway_0208350c, &hitWall);
        SweepWorldCollision_020364a0(&sweep);
        if (hitWall) {
            dir = object->velocity;
        } else {
            object->velocity.x = 0;
            object->velocity.z = 0;
        }
    }
    if (!tooClose) {
        int turn = (s16)((s16)AngleBetweenXy_0204a508(&forward, &dir) * Sign(DotFx32Xy_0204a390(&right, &dir)));

        if ((turn < 0 ? -turn : turn) > 0xaaa) {
            object->angle = object->angle - (s16)((s64)Sign(turn) * 0xaaa);
        } else {
            object->angle = object->angle - turn;
        }
        object->rotation = 0x3fff - object->angle;
    }
    idx = (u16)object->angle >> 4;
    heading = MakeVec2(data_0205356c[(0x400 - idx) & 0xfff], data_0205356c[idx]);
    stepTmp.x = heading.x;
    stepTmp.y = 0;
    stepTmp.z = heading.z;
    step = stepTmp;
    VEC_MultAdd_01ffa09c(0x133, &step, &object->push, &moved);
    SetShapeDelta(&object->body->shape, &moved);
    object->push = data_02053438;
    groundFilter = MakeFilter(0, 0x15);
    CollisionQuery_Init_02034c74(&groundQuery, 0, object->body->actor, 0xb, 0, 1, &object->body->shape, &groundWorkspace, &groundFilter);
    groundSweep = groundQuery;
    motion = object->body->shape.delta;
    landed = FALSE;
    object->blocked = 0;
    groundSweep.filter = MakeCallback(CanTriggerOnContact_02083320, object);
    groundSweep.contact = MakeCallback(FieldObject_HandlePush_0208334c, object);
    FieldObject_SetSavedValue_0207f9c8(object, 0);
    hit = SweepWorldCollision_020364a0(&groundSweep);
    if (object->touched && !object->blocked) {
        object->touched = 0;
        SetSlotLayoutHighlight_0207d45c(0);
    }
    if (!tooClose) {
        if (hit != NULL) {
            object->position = hit->position;
            object->position.y -= 0xccd;
            if (func_01ffa0f4(&object->position, target) > 0x8000) {
                landed = TRUE;
            } else {
                VEC_Subtract_01ff9e3c(&hit->normal, &motion, &normalDeltaRaw);
                normalDelta = normalDeltaRaw;
                if (normalDelta.x != 0 || normalDelta.z != 0) {
                    fx32 length = FX_Sqrt_01ff9cfc((fx32)(((fx64)hit->normal.x * hit->normal.x + (fx64)hit->normal.z * hit->normal.z) >> 12));
                    if (length > FixedPointMultiply12(0x133, 0x800)) {
                        object->velocity = MakeVec2(hit->normal.x, hit->normal.z);
                        NormalizeXy_0204a3e4(&object->velocity);
                    } else {
                        object->velocity = MakeVec2(normalDelta.z * object->direction, -normalDelta.x * object->direction);
                        NormalizeXy_0204a3e4(&object->velocity);
                    }
                    {
                        VecFx32 flat;

                        flat.x = object->velocity.x;
                        flat.y = 0;
                        flat.z = object->velocity.z;
                        turned = flat;
                    }
                    func_0204b0ac(&turned, &motion, 0x165);
                    object->velocity.x = turned.x;
                    object->velocity.z = turned.z;
                } else {
                    landed = TRUE;
                }
            }
        } else {
            VEC_Add_01ff9e0c(&object->position, &object->body->shape.delta, &object->position);
            landed = TRUE;
        }
    }
    if (!tooClose && landed && (object->velocity.x != 0 || object->velocity.z != 0)) {
        object->velocity.x = 0;
        object->velocity.z = 0;
        object->direction = -object->direction;
    }
done:
    FallCylinderObject_020831a8(object);
    FieldObject_SyncActorTransform_0208352c(object);
    return 0;
}
