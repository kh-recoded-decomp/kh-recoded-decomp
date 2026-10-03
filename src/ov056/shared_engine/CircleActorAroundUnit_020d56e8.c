#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x14];
    fx32 duration;
    u8 pad_18[0x50 - 0x18];
    fx32 radius;
} CircleDef;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 w;
} QuatFx32;

typedef struct {
    u8 pad_000[0x200];
    QuatFx32 spin;
    fx32 facingOffset;
    fx32 step;
} CircleParams;

typedef struct {
    u8 pad_000[0x18];
    VecFx32 position;
    u8 pad_024[0x138 - 0x24];
    CircleDef *def;
    u8 pad_13c[0x150 - 0x13c];
    CircleParams *params;
} CircleUnit;

typedef struct {
    u8 pad_000[0x18c];
    fx32 tangentScale;
} CircleOwner;

typedef struct {
    VecFx32 target;
    VecFx32 velocity;
    VecFx32 tangent;
    VecFx32 offset;
    fx32 elapsed;
    CircleOwner *owner;
    CircleUnit *unit;
    s32 state;
} CircleWork;

typedef struct {
    u8 pad_00[0x10];
    s16 actorId;
} CircleEvent;

typedef struct StageActor {
    u8 pad_000[0x2e6];
    u16 facing;
} StageActor;

extern const VecFx32 data_ov056_020d7f58;

extern StageActor *GetStageActor_0209c040(int id);
extern VecFx32 *func_ov001_02090f04(StageActor *actor);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern int FixedPointMultiply12(int left, int right);
extern void func_0202fba8(VecFx32 *in, QuatFx32 *rotation, VecFx32 *out);
extern void HermiteInterpolateVec_020d5348(VecFx32 *out, const VecFx32 *start, const VecFx32 *end, const VecFx32 *startTangent, const VecFx32 *endTangent, fx32 t);
extern void ClearActorMotionState_02091194(StageActor *actor);
extern void ClearActorMotionSpeed_020911a8(StageActor *actor);
extern void AddObjectOffsetVector_02091c50(StageActor *actor, VecFx32 *offset);
extern void SetActorFacingDegrees_02090f3c(StageActor *actor, int degrees);
extern void func_ov001_020958e4(CircleEvent *event, int status);

BOOL CircleActorAroundUnit_020d56e8(CircleEvent *event, CircleWork *work)
{
    CircleOwner *owner = work->owner;
    CircleUnit *unit = work->unit;
    CircleParams *params = unit->params;
    StageActor *actor = GetStageActor_0209c040(event->actorId);
    fx32 step = params->step;
    fx32 radius;
    fx32 radiusSq;
    fx32 t;
    VecFx32 dir;
    VecFx32 side;
    VecFx32 next;
    VecFx32 pos;
    VecFx32 delta;

    switch (work->state) {
    default:
        work->state = 0;
    case 0:
        func_ov001_020958e4(event, 9);
        break;
    case 1:
        radius = unit->def->radius;
        radiusSq = FixedPointMultiply12(radius, radius);
        VEC_Subtract_01ff9e3c(func_ov001_02090f04(actor), &unit->position, &dir);
        if (VEC_DotProduct_01ff9e6c(&dir, &dir) < radiusSq) {
            dir.x = 0;
            dir.y = 0;
            dir.z = 0x1000;
        }
        VEC_CrossProduct_01ff9ea8(&data_ov056_020d7f58, &dir, &side);
        VEC_Normalize_01ff9f88(&side, &side);
        VEC_MultAdd_01ffa09c(radius, &side, &unit->position, &work->target);
        VEC_CrossProduct_01ff9ea8(&side, &data_ov056_020d7f58, &dir);
        ScaleVecFx32_01ffafb4(owner->tangentScale, &dir, &work->tangent);
        work->velocity.z = 0;
        work->velocity.y = 0;
        work->velocity.x = 0;
        work->elapsed = 0;
        work->state = 2;
    case 2:
        if (work->elapsed + step <= unit->def->duration) {
            t = FX_Div_01ff9c84(step, unit->def->duration - work->elapsed);
            pos = *func_ov001_02090f04(actor);
            HermiteInterpolateVec_020d5348(&next, &pos, &work->target, &work->velocity, &work->tangent, t);
            VEC_Subtract_01ff9e3c(&next, &pos, &work->velocity);
            ClearActorMotionState_02091194(actor);
            ClearActorMotionSpeed_020911a8(actor);
            AddObjectOffsetVector_02091c50(actor, &work->velocity);
            work->elapsed += step;
            break;
        }
        VEC_Subtract_01ff9e3c(func_ov001_02090f04(actor), &unit->position, &work->offset);
        work->state = 3;
    case 3:
        delta = *func_ov001_02090f04(actor);
        func_0202fba8(&work->offset, &params->spin, &work->offset);
        VEC_Add_01ff9e0c(&unit->position, &work->offset, &delta);
        ClearActorMotionState_02091194(actor);
        ClearActorMotionSpeed_020911a8(actor);
        VEC_Subtract_01ff9e3c(&delta, func_ov001_02090f04(actor), &delta);
        AddObjectOffsetVector_02091c50(actor, &delta);
        SetActorFacingDegrees_02090f3c(actor, params->facingOffset + (fx32)(((s64)actor->facing * 0x1680000 + 0x80000) >> 20));
        break;
    }
    return FALSE;
}
