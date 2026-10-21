#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitCallback {
    void *func;
    void *context;
} HitCallback;

typedef struct QueryWorkspace {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct CollisionQuery {
    u8 pad_00[0x58];
    HitCallback callback;
} CollisionQuery;

typedef struct ActorBody {
    VecFx32 *shape;
    s32 bounds[6];
    s32 shapeKind;
    VecFx32 delta;
    s32 sweptBounds[6];
} ActorBody;

typedef struct Actor {
    u8 pad_000[0x130];
    ActorBody body;
} Actor;

typedef struct RecordSlot {
    u8 pad_00[8];
    u16 flags;
} RecordSlot;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[0xc];
    u16 flags;
    s8 state;
    u8 pad_53;
    fx32 cooldown;
    u8 pad_58[0xc];
    VecFx32 velocity;
    VecFx32 axisA;
    VecFx32 axisB;
    VecFx32 spin;
    u8 pad_94[0x10];
    s32 areaId;
} FieldObject;

extern Actor *func_02036240(u32 id);
extern int func_ov031_020bc738(void);
extern RecordSlot *func_02036810(u32 id);
extern void func_02036924(int index);
extern int AdvanceObjectAnimations_020a2bf8(FieldObject *obj);
extern VecFx32 *func_ov001_0206dc4c(int arg);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *in, VecFx32 *out);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *in, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void ScaleVecFx32ComponentsConditional_0204b6c4(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern int FixedPointMultiply12(int left, int right);
extern void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D,
                                         void *shape, QueryWorkspace *workspace, void *unk44);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void FieldObject_SetDisabled_020a333c(FieldObject *obj, BOOL disable);
extern void func_02036974(int index);
extern void SetShapePosition_0203afa0(void *shape, const VecFx32 *position);
extern void func_ov018_020a3134(void);


int FieldObject_UpdatePushedMotion_020a2c84(FieldObject *obj)
{
    QueryWorkspace workspace;
    CollisionQuery query;
    CollisionQuery queryInit;
    VecFx32 toPlayer;
    VecFx32 lift;
    VecFx32 side;
    VecFx32 heading;
    VecFx32 forward;
    VecFx32 push;
    VecFx32 spinAxis;
    VecFx32 flat;
    VecFx32 yAxisA;
    VecFx32 yAxisB;
    VecFx32 yAxisC;
    VecFx32 offset;
    VecFx32 diff;
    VecFx32 up;
    VecFx32 liftIn;
    VecFx32 sideIn;
    VecFx32 flatIn;
    VecFx32 headingIn;
    VecFx32 yAxisAIn;
    VecFx32 yAxisBIn;
    VecFx32 yAxisCIn;
    VecFx32 normal;
    VecFx32 offsetIn;
    VecFx32 sum;
    VecFx32 raised;
    HitCallback callback;
    Actor *actor;
    Actor *moved;
    fx32 dist;
    fx32 closeness;
    fx32 span;
    fx32 limit;
    fx32 turn;
    fx32 mag;
    fx32 height;
    fx32 elapsed;
    fx32 strength;
    s32 sign;
    s32 flagBit;
    VecFx32 *toPlayerDir;

    elapsed = 0;
    flagBit = 1;
    toPlayerDir = &toPlayer;
    if (obj->flags & 8) {
        return 0;
    }
    if (obj->flags & 0x800) {
        return 0;
    }
    actor = func_02036240(obj->actorId);
    if (obj->areaId == func_ov031_020bc738()) {
        return 0;
    }
    if (obj->cooldown != 0) {
        obj->cooldown -= 0x1000;
        if (obj->cooldown <= 0) {
            obj->cooldown = 0;
            if (!(func_02036810(obj->actorId)->flags & 0x100)) {
                func_02036924(obj->actorId);
            }
        }
    }
    if (obj->state == 1) {
        return AdvanceObjectAnimations_020a2bf8(obj);
    }
    if (obj->flags & (flagBit << 10)) {
        VEC_Subtract_01ff9e3c(actor->body.shape, func_ov001_0206dc4c(0), &diff);
        toPlayer = diff;
        toPlayer.y = elapsed;
        dist = VEC_Normalize_01ffaff4(toPlayerDir, toPlayerDir);
        if (dist < 0x8000) {
            closeness = FX_Div_01ff9c84(0x8000 - dist, 0x8000);
            mag = FX_Sqrt_01ff9cfc(FX_Div_01ff9c84(closeness > 0x800 ? 0x800 : closeness, 0x800));
            up.x = 0;
            up.y = mag;
            up.z = 0;
            liftIn = up;
            ScaleVecFx32ComponentsConditional_0204b6c4(&liftIn, 0x148, flagBit);
            lift = liftIn;
            span = 0x3000 - elapsed;
            RotateVectorAroundAxis_0204b34c(&lift, toPlayerDir, FixedPointMultiply12(FX_Div_01ff9c84(span, 0x3000), -0x860));
            VEC_Add_01ff9e0c(&obj->velocity, &lift, &obj->velocity);
            if (obj->velocity.x != 0 || obj->velocity.z != 0) {
                if (closeness > 0x333) {
                    closeness = 0x333;
                }
                closeness = FX_Sqrt_01ff9cfc(FX_Div_01ff9c84(closeness, 0x333));
                limit = FixedPointMultiply12(closeness, FixedPointMultiply12(FX_Div_01ff9c84(span, 0x3000), 0x430));
                sideIn.x = -toPlayer.z;
                sideIn.y = 0;
                sideIn.z = toPlayer.x;
                side = sideIn;
                flatIn.x = obj->velocity.x;
                flatIn.y = 0;
                flatIn.z = obj->velocity.z;
                flat = flatIn;
                VEC_NormalizeUnchecked_01ff9f88(&flat, &headingIn);
                heading = headingIn;
                forward = toPlayer;
                yAxisAIn.x = 0;
                yAxisAIn.y = 0x1000;
                yAxisAIn.z = 0;
                yAxisA = yAxisAIn;
                RotateVectorAroundAxis_0204b34c(&forward, &yAxisA, 0xdf6);
                yAxisBIn.x = 0;
                yAxisBIn.y = 0x1000;
                yAxisBIn.z = 0;
                yAxisB = yAxisBIn;
                RotateVectorAroundAxis_0204b34c(&side, &yAxisB, 0xdf6);
                sign = VEC_DotProduct_01ff9e6c(&heading, &forward) >= 0 ? 1 : -1;
                turn = (s8)sign * (s32)((s64)AngleBetweenVecs_0204b070(&side, &heading) * 0x6488 / 0x10000);
                if (limit > turn) {
                    limit = turn;
                }
                yAxisCIn.x = 0;
                yAxisCIn.y = 0x1000;
                yAxisCIn.z = 0;
                yAxisC = yAxisCIn;
                RotateVectorAroundAxis_0204b34c(&obj->velocity, &yAxisC, limit);
                push = up;
                RotateVectorAroundAxis_0204b34c(&push, toPlayerDir, FixedPointMultiply12(FX_Div_01ff9c84(span, 0x3000), 0x860));
                NegateVecFx32_0204aa40(&push);
                ScaleVecFx32InPlace_0204a5e4(&push, 0x2ca);
                VEC_Subtract_01ff9e3c(&push, &obj->spin, &push);
                VEC_MultAdd_01ffa09c(0x333, &push, &obj->spin, &obj->spin);
            }
        }
        obj->velocity.y -= 0xcd;
        ScaleVecFx32InPlace_0204a5e4(&obj->velocity, 0xe66);
        ScaleVecFx32InPlace_0204a5e4(&obj->spin, 0xf33);
        mag = VEC_Normalize_01ffaff4(&obj->spin, &normal);
        spinAxis = normal;
        RotateVectorAroundAxis_0204b34c(&obj->axisA, &spinAxis, mag);
        VEC_NormalizeUnchecked_01ff9f88(&obj->axisA, &obj->axisA);
        RotateVectorAroundAxis_0204b34c(&obj->axisB, &spinAxis, mag);
        moved = func_02036240(obj->actorId);
        CollisionQuery_Init_02034c74(&queryInit, 0, moved, 6, 0, 1, &moved->body, &workspace, moved + 1);
        query = queryInit;
        callback.func = func_ov018_020a3134;
        callback.context = obj;
        query.callback = callback;
        moved->body.delta = obj->velocity;
        OffsetBoxByDelta_0203ac70(moved->body.bounds, moved->body.sweptBounds, &moved->body.delta);
        SweepWorldCollision_020364a0(&query);
        VEC_Add_01ff9e0c(&obj->position, &moved->body.delta, &obj->position);
        height = actor->body.shape->y;
        if (height > 0xf000 || obj->velocity.y < 0) {
            if (obj->flags & 0x1000) {
                FieldObject_SetDisabled_020a333c(obj, TRUE);
            } else {
                obj->flags |= 0x800;
                obj->flags &= ~0x400;
                func_02036974(obj->actorId);
            }
        } else if (height < 0x800) {
            height = 0x800 - height;
            offsetIn.x = 0;
            offsetIn.y = height;
            offsetIn.z = 0;
            offset = offsetIn;
            VEC_Add_01ff9e0c(actor->body.shape, &offset, &sum);
            raised = sum;
            SetShapePosition_0203afa0(&actor->body, &raised);
            OffsetBoxByDelta_0203ac70(actor->body.bounds, actor->body.sweptBounds, &actor->body.delta);
            obj->position.y += height;
        }
    }
    return 0;
}
