#pragma opt_common_subs off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Box {
    s32 maxX, maxY, maxZ;
    s32 minX, minY, minZ;
} Box;

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

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

typedef struct QueryWorkspace {
    u8 pad_000[0xc0];
    VecFx32 normals[16];
    u8 normalCount;
    u8 pad_181[0x23];
} QueryWorkspace;

typedef struct QueryFilter {
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct QueryHandler {
    void *func;
    void *arg;
} QueryHandler;

typedef struct CollisionQuery {
    u32 words[0x12];
    QueryHandler surface;
    QueryHandler contact;
    QueryHandler bounce;
} CollisionQuery;

typedef struct ShapeHit {
    u8 pad_00[0x10];
    s32 depth;
    u8 pad_14[4];
} ShapeHit;

typedef struct SweepHit {
    u8 pad_00[0x2c];
    VecFx32 push;
} SweepHit;

typedef struct ContactProbe {
    void *object;
    const VecFx32 *direction;
} ContactProbe;

typedef struct PatrolModel {
    u8 pad_00[0x10];
    u8 anchor[4];
    u16 anim[1];
    u8 pad_16[0xb8 - 0x16];
    VecFx32 translation;
    u8 pad_c4[0x11c - 0xc4];
    u8 collider[0x140 - 0x11c];
    SweptShape sweep;
} PatrolModel;

typedef struct PatrolPoints {
    VecFx32 *points;
} PatrolPoints;

typedef struct PatrolObject {
    u8 pad_00[0x0c];
    PatrolModel *model;
    u8 pad_10[0x04];
    void *state;
    u8 pad_18[0x20];
    u8 actorId;
    u8 pad_39[0x07];
    VecFx32 position;
    u8 pad_4c[0x0c];
    s32 moving;
    fx32 idleTime;
    u8 pad_60[0x04];
    VecFx32 heading;
    VecFx32 up;
    u8 pad_7c[0x03];
    s8 lastPoint;
    s8 targetPoint;
    u8 visits;
    u8 paused;
} PatrolObject;

typedef int (*StaticCollideFn)(CollisionShape *a, CollisionShape *b, ShapeHit *hit, int flags);
typedef int (*MovingCollideFn)(CollisionShape *a, CollisionShape *b, ShapeHit *hit, int flags, VecFx32 *delta);

extern StaticCollideFn data_020558a0[][6];
extern MovingCollideFn data_02055930[][6];

extern BOOL DetachFromLeaderQuadTree_020836d8(PatrolObject *object);
extern int Anim_GetFrame_0202f4a0(u16 *anim, int index);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern u32 func_ov001_02063a4c(void);
extern void SetSavedValueFlag7_02084750(PatrolObject *object, int flag);
extern void SetPackedStateLowBit_02084774(PatrolObject *object, u16 lowBit);
extern void UpdateFieldPointActivation_02083dbc(PatrolObject *object);
extern BOOL ActorSlot_IsFlag8SetByIndex_02036164(int index);
extern PatrolPoints *FindActiveSlotEntry_02083c38(PatrolObject *object);
extern void SetCollisionObjectPosition_02033f48(void *object, const VecFx32 *position);
extern int func_ov001_02067ed4(void);
extern BOOL ComputeNamedPointBounds_02068268(int setIndex, int recordIndex, VecFx32 *outMin, VecFx32 *outMax);
extern VecFx32 AverageVecs_0204b604(int count, ...);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 FX_Sqrt_01ff9cfc(fx32 x);
extern int FixedPointMultiply12(int left, int right);
extern int UpdatePatrolIdle_02083e70(PatrolObject *object);
extern void FieldObject_AdvanceRandomVariant_020846a4(PatrolObject *object);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void ScaleVecHighShift_0204a640(VecFx32 *vec, s32 scale);
extern CollisionShape MakeSphereShape_0203ad14(Sphere *sphere, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern SweepHit *SweepWorldCollision_020364a0(CollisionQuery *query);
extern BOOL func_ov001_020845dc(void *record, PatrolObject *object);
extern BOOL IsContactBlockingProbe_02084660(void *ref, void *body, ContactProbe *probe);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern void RotateVecTowardVec_0204b0ac(VecFx32 *vec, const VecFx32 *target, fx32 angle);
extern void TurnVecTowardVecLimited_0204b1fc(VecFx32 *vec, const VecFx32 *target, fx32 maxAngle);
extern void func_ov001_02083d2c(PatrolObject *object);

static inline QueryFilter MakeFilter(s32 unk, s32 mask)
{
    QueryFilter filter;
    filter.unk_00 = unk;
    filter.mask = mask;
    return filter;
}

static inline QueryHandler MakeHandler(void *func, void *arg)
{
    QueryHandler handler;
    handler.func = func;
    handler.arg = arg;
    return handler;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline int TestSweptShape(SweptShape *mover, CollisionShape *target, ShapeHit *hit)
{
    int mode;

    if (mover->sweptBounds.maxX >= target->bounds.minX
        && mover->sweptBounds.minX <= target->bounds.maxX
        && mover->sweptBounds.maxZ >= target->bounds.minZ
        && mover->sweptBounds.minZ <= target->bounds.maxZ
        && mover->sweptBounds.maxY >= target->bounds.minY
        && mover->sweptBounds.minY <= target->bounds.maxY) {
        if (mover->delta.x == 0 && mover->delta.y == 0 && mover->delta.z == 0) {
            mode = 2;
        } else {
            mode = 1;
        }
    } else {
        mode = 0;
    }
    if (mode != 0) {
        int result;
        if (mode == 2) {
            result = data_020558a0[mover->shape.kind][target->kind](&mover->shape, target, hit, 6);
        } else {
            result = data_02055930[mover->shape.kind][target->kind](&mover->shape, target, hit, 4, &mover->delta);
        }
        return result;
    }
    return 0;
}

static inline VecFx32 ScaledCopy(const VecFx32 *src, fx32 scale)
{
    VecFx32 out = *src;
    ScaleVecFx32InPlace_0204a5e4(&out, scale);
    return out;
}

static inline void DirectionBetween(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VecFx32 out;
    VecFx32 unit;
    VEC_Subtract_01ff9e3c(a, b, &out);
    diff = out;
    VEC_NormalizeUnchecked_01ff9f88(&diff, &unit);
}

static inline VecFx32 RemoveComponent(const VecFx32 *v, const VecFx32 *normal)
{
    VecFx32 along;
    VecFx32 scaled;
    VecFx32 result;
    fx32 dot = VEC_DotProduct_01ff9e6c(v, normal);
    scaled = *normal;
    ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
    along = scaled;
    VEC_Subtract_01ff9e3c(v, &along, &result);
    return result;
}

static inline VecFx32 RotatedCopy(const VecFx32 *src, const VecFx32 *target, fx32 angle)
{
    VecFx32 out = *src;
    RotateVecTowardVec_0204b0ac(&out, target, angle);
    return out;
}

static inline void SetSweepDeltaValue(SweptShape *sweep, VecFx32 delta)
{
    sweep->delta = delta;
    OffsetBoxByDelta_0203ac70(&sweep->shape.bounds, &sweep->sweptBounds, &sweep->delta);
}

static inline CollisionShape BuildSphere(Sphere *sphere, const VecFx32 *center, fx32 radius)
{
    return MakeSphereShape_0203ad14(sphere, center, radius);
}

int UpdatePatrolMove_02083f9c(PatrolObject *object)
{
    SweptShape moverShape;
    QueryWorkspace workspace;
    CollisionQuery sweep;
    QueryWorkspace groundWorkspace;
    CollisionQuery groundSweep;
    SweptShape shape;
    CollisionQuery query;
    CollisionQuery groundQuery;
    VecFx32 savedPos;
    VecFx32 target;
    VecFx32 boundsMax;
    VecFx32 boundsMin;
    VecFx32 dir;
    Sphere selfSphere;
    Sphere targetSphere;
    CollisionShape targetShape;
    ShapeHit hit;
    VecFx32 slide;
    VecFx32 turned;
    VecFx32 push;
    VecFx32 delta;
    VecFx32 worldUp;
    VecFx32 unit;
    VecFx32 diff;
    VecFx32 toTarget;
    VecFx32 faceDir;
    QueryFilter filter;
    ContactProbe probe;
    QueryFilter groundFilter;
    PatrolPoints *entry;
    int index;
    fx32 dist;
    fx32 dirX;
    BOOL zero;
    BOOL flat;
    int contact;
    int angle;
    fx32 scale;
    SweepHit *groundHit;
    int frame;
    PatrolModel *model;

    if (DetachFromLeaderQuadTree_020836d8(object)) {
        frame = (Anim_GetFrame_0202f4a0(object->model->anim, 0) >> 12) - 1;
        if ((frame - 2) % 6 == 0) {
            SpawnSoundSlot_0204da8c(0xe7, 4, &object->position, 2);
        }
    }
    if (func_ov001_02063a4c() != 4 || object->paused != 0) {
        if (func_ov001_02063a4c() != 4 && object->paused != 0) {
            object->paused = 0;
        }
        SetSavedValueFlag7_02084750(object, 0);
        SetPackedStateLowBit_02084774(object, 0);
    } else {
        UpdateFieldPointActivation_02083dbc(object);
        if (ActorSlot_IsFlag8SetByIndex_02036164(object->actorId)) {
            savedPos = object->position;
            entry = FindActiveSlotEntry_02083c38(object);
            SetCollisionObjectPosition_02033f48(object->model->collider, &object->position);
            index = object->targetPoint;
            if (index < 0) {
                ComputeNamedPointBounds_02068268(func_ov001_02067ed4(), (s8)(-1 - index), &boundsMin, &boundsMax);
                target = AverageVecs_0204b604(2, &boundsMin, &boundsMax);
            } else {
                target = entry->points[index];
            }
            VEC_Subtract_01ff9e3c(&target, &object->position, &diff);
            toTarget = diff;
            dist = VEC_Normalize_01ffaff4(&toTarget, &unit);
            faceDir = unit;
            dir = unit;
            if (dist <= 0x333) {
                object->heading = faceDir;
                object->position = entry->points[object->targetPoint];
                SetCollisionObjectPosition_02033f48(object->model->collider, &object->position);
                object->moving = 0;
                object->state = UpdatePatrolIdle_02083e70;
                object->idleTime = 0;
                if (object->targetPoint < 0) {
                    FieldObject_AdvanceRandomVariant_020846a4(object);
                } else {
                    object->lastPoint = object->targetPoint;
                    SetSavedValueFlag7_02084750(object, 1);
                }
            } else {
                zero = FALSE;
                flat = FALSE;
                dirX = dir.x;
                if (dirX == 0 && dir.y == 0) {
                    flat = TRUE;
                }
                if (flat && dir.z == 0) {
                    zero = TRUE;
                }
                if (!zero) {
                    delta = ScaledCopy(&object->heading, 0x3000);
                    shape.shape = MakeSphereShape_0203ad14(&selfSphere, &object->position, 0x800);
                    shape.delta = delta;
                    OffsetBoxByDelta_0203ac70(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
                    moverShape = shape;
                    targetShape = BuildSphere(&targetSphere, &target, 0x266);
                    contact = TestSweptShape(&moverShape, &targetShape, &hit);
                    if (contact && hit.depth != -1) {
                        ScaleVecHighShift_0204a640(&moverShape.delta, hit.depth);
                    }
                    if (!contact || hit.depth != -1) {
                        filter = MakeFilter(0, 0x16);
                        CollisionQuery_Init_02034c74(&query, 0, object->model->anchor, 0xf, 1, 1, &moverShape, &workspace, &filter);
                        sweep = query;
                        probe.direction = &dir;
                        probe.object = object;
                        sweep.surface = MakeHandler((void *)func_ov001_020845dc, object);
                        sweep.contact = MakeHandler((void *)IsContactBlockingProbe_02084660, &probe);
                        if (SweepWorldCollision_020364a0(&sweep) && (moverShape.delta.x != dirX || moverShape.delta.y != dir.y || moverShape.delta.z != dir.z)) {
                            DirectionBetween(&dir, &moverShape.delta);
                            slide = RemoveComponent(&dir, &workspace.normals[workspace.normalCount - 1]);
                            if (slide.x != 0 || slide.y != 0 || slide.z != 0) {
                                angle = ((s64)AngleBetweenVecs_0204b070(&dir, &slide) * 0x6488) / 0x10000;
                                scale = FX_Sqrt_01ff9cfc(0x1000 - FX_Div_01ff9c84(VEC_Mag_01ff9f28(&moverShape.delta), 0x3000));
                                angle = FixedPointMultiply12(angle, scale);
                                turned = RotatedCopy(&faceDir, &slide, angle);
                                TurnVecTowardVecLimited_0204b1fc(&object->heading, &turned, 0x595);
                                VEC_NormalizeUnchecked_01ff9f88(&object->heading, &object->heading);
                            } else {
                                object->heading = faceDir;
                            }
                        } else {
                            object->heading = faceDir;
                        }
                    }
                    if (object->heading.x != 0 || object->heading.z != 0) {
                        worldUp = MakeVec(0, 0x1000, 0);
                        TurnVecTowardVecLimited_0204b1fc(&object->up, &worldUp, 0x595);
                    }
                    SetSweepDeltaValue(&object->model->sweep, ScaledCopy(&object->heading, 0x333));
                    groundFilter = MakeFilter(0, 0x15);
                    model = object->model;
                    CollisionQuery_Init_02034c74(&groundQuery, 0, model->anchor, 7, 0, 1, &model->sweep, &groundWorkspace, &groundFilter);
                    groundSweep = groundQuery;
                    groundSweep.surface = MakeHandler((void *)func_ov001_020845dc, object);
                    groundHit = SweepWorldCollision_020364a0(&groundSweep);
                    if (groundHit && (groundHit->push.x != 0 || groundHit->push.y != 0 || groundHit->push.z != 0)) {
                        push = groundHit->push;
                        VEC_Normalize_01ffaff4(&push, &push);
                        ScaleVecFx32InPlace_0204a5e4(&push, 0x333);
                        SetSweepDeltaValue(&object->model->sweep, push);
                    }
                    VEC_Add_01ff9e0c(&object->position, &object->model->sweep.delta, &object->position);
                } else {
                    VEC_Add_01ff9e0c(&object->position, &object->model->sweep.delta, &object->position);
                }
            }
            SetCollisionObjectPosition_02033f48(object->model->collider, &savedPos);
            object->model->translation = object->position;
        }
    }
    func_ov001_02083d2c(object);
    return 0;
}

