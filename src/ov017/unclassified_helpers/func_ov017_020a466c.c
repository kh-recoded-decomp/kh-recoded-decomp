#include "nitro/types.h"
#include "nitro/fx_types.h"

#pragma opt_common_subs off

typedef struct MotionState {
    VecFx32 velocity;
    BOOL bounced;
} MotionState;

typedef struct FieldLink {
    u8 pad_00[4];
    s32 snapToGrid;
} FieldLink;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 slot;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[6];
    s8 state;
    u8 pad_4b[0x15];
    FieldLink *link;
} FieldObject;

typedef struct Actor {
    u8 pad_000[0x130];
    void *shape;
    s32 box[1];
    fx32 top;
    s32 pad_13c[2];
    fx32 bottom;
    s32 pad_148;
    s32 shapeKind;
    VecFx32 delta;
    s32 sweptBox[6];
} Actor;

typedef struct HitInfo {
    u8 pad_00[0x2c];
    VecFx32 normal;
    VecFx32 position;
} HitInfo;

typedef struct QueryWorkspace {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct QueryCallback {
    void *func;
    void *context;
} QueryCallback;

typedef struct QueryFilter {
    void *context;
    s32 mask;
} QueryFilter;

typedef struct CollisionQuery {
    u8 pad_00[0x48];
    QueryCallback filter;
    QueryCallback check;
    QueryCallback resolve;
} CollisionQuery;

extern Actor *func_02036240(u32 id);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetShapePosition_0203afa0(void *shape, const VecFx32 *position);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern HitInfo *SweepWorldCollision_020364a0(CollisionQuery *query);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern int FixedPointMultiply12(int left, int right);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern BOOL func_ov017_020a44e8(void);
extern BOOL func_ov017_020a4528(void);
extern BOOL func_ov017_020a4574(void);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline VecFx32 VecNeg(VecFx32 vec)
{
    NegateVecFx32_0204aa40(&vec);
    return vec;
}

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Add_01ff9e0c(a, b, &result);
    return result;
}

static inline VecFx32 VecNormalize(const VecFx32 *v)
{
    VecFx32 result;
    func_01ffaff4(v, &result);
    return result;
}

static inline fx32 Normalize(const VecFx32 *v, VecFx32 *out)
{
    VecFx32 result;
    fx32 length = func_01ffaff4(v, &result);
    *out = result;
    return length;
}

static inline VecFx32 VecScaled(const VecFx32 *v, fx32 scale)
{
    VecFx32 result = *v;
    ScaleVecFx32InPlace_0204a5e4(&result, scale);
    return result;
}

static inline QueryFilter MakeFilter(void *context, s32 mask)
{
    QueryFilter filter;
    filter.context = context;
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

int func_ov017_020a466c(MotionState *motion, FieldObject *obj)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    VecFx32 move;
    VecFx32 offset;
    VecFx32 surface;
    VecFx32 direction;
    VecFx32 step;
    VecFx32 center;
    VecFx32 negOffset;
    VecFx32 normal;
    QueryFilter filter;
    Actor *actor;
    HitInfo *hit;
    fx32 length;

    if (obj->state != 0) {
        return 0;
    }
    motion->velocity.y -= 0x80;
    step = motion->velocity;
    move = step;
    filter = MakeFilter(motion, 9);
    actor = func_02036240(obj->slot);
    offset = MakeVec(0, -(actor->top - actor->bottom) / 2, 0);
    negOffset = VecNeg(offset);
    center = VecAdd(&obj->position, &negOffset);
    SetShapePosition_0203afa0(&actor->shape, &center);
    OffsetBoxByDelta_0203ac70(actor->box, actor->sweptBox, &actor->delta);
    actor->delta = step;
    OffsetBoxByDelta_0203ac70(actor->box, actor->sweptBox, &actor->delta);
    CollisionQuery_Init_02034c74(&query, 0, actor, 0xf, 0, 1, &actor->shape, &workspace, &filter);
    sweep = query;
    motion->bounced = FALSE;
    sweep.filter = MakeCallback(func_ov017_020a44e8, obj);
    sweep.check = MakeCallback(func_ov017_020a4528, NULL);
    sweep.resolve = MakeCallback(func_ov017_020a4574, motion);
    hit = SweepWorldCollision_020364a0(&sweep);
    if (hit != NULL) {
        obj->position = VecAdd(&hit->position, &offset);
        if (obj->link->snapToGrid != 0 && motion->velocity.x == 0 && motion->velocity.y == 0 && motion->velocity.z == 0) {
            obj->position.x &= ~0x3f;
            obj->position.y &= ~0x3f;
            return 1;
        }
        if (!motion->bounced) {
            Normalize(&hit->normal, &normal);
            surface = normal;
            length = Normalize(&motion->velocity, &direction);
            motion->velocity = VecScaled(&normal, FixedPointMultiply12(length, VEC_DotProduct_01ff9e6c(&direction, &surface)));
        }
    } else {
        if (VEC_Mag_01ff9f28(&motion->velocity) > 0xa000) {
            return 1;
        }
        VEC_Add_01ff9e0c(&obj->position, &move, &obj->position);
    }
    return 0;
}



