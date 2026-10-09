#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct {
    Sphere *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void *func;
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x14];
    QueryCallback filter;
    QueryCallback callback;
} CollisionQuery;

typedef struct {
    VecFx32 row[3];
} BasisMatrix;

typedef struct {
    void *object;
    s32 type;
} TargetRef;

typedef struct {
    s32 kind;
    u8 pad_04[0x10 - 0x4];
    TargetRef target;
    u8 pad_18[4];
    u32 flags;
    fx32 animTime;
    u8 pending;
    u8 pad_25[3];
    fx32 timer;
    fx32 interval;
    fx32 boostTime;
    fx32 boostDuration;
    VecFx32 lastTargetPos;
    fx32 baseSpeed;
} SeekerState;

typedef struct {
    u8 pad_00[0xc];
    fx32 radius;
} SeekerDef;

typedef struct {
    u8 pad_000[2];
    s8 status;
    u8 pad_003[0x24 - 0x3];
    VecFx32 velocity;
    u8 anim[0xd4 - 0x30];
    VecFx32 position;
    u8 pad_0e0[0x138 - 0xe0];
    SeekerDef *def;
    u8 pad_13c[0x150 - 0x13c];
    SeekerState *state;
} Seeker;

typedef struct {
    u8 pad_000[0x230];
    void *actor;
} SeekerWorld;

typedef struct {
    u8 data[0x104];
} AnimSlot;

typedef struct {
    u8 pad_00[0x44];
    SeekerWorld *world;
    AnimSlot slots[1];
} SeekerContext;

extern s16 data_0205356c[];

#define ANGLE_INDEX(angle) ((s32)((((s64)(angle) << 16) / 0x6488) & 0xffff) >> 4)
#define SIN_AT(index) data_0205356c[index]
#define COS_AT(index) data_0205356c[(0x400 - (index)) & 0xfff]

extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *source, VecFx32 *destination);
extern int FixedPointMultiply12(int left, int right);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern fx32 func_0202f4b8(void *anim, int arg);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern CollisionShape MakeSphereShape_0203ad14(Sphere *sphere, const VecFx32 *center, fx32 radius);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern VecFx32 PickPerpendicularAxis_0204acb0(const VecFx32 *vec);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern void RotateVecTowardVec_0204b0ac(VecFx32 *vec, const VecFx32 *target, fx32 angle);
extern void BuildBasisMatrix_0204bf28(const VecFx32 *forward, const VecFx32 *up, BasisMatrix *out);
extern int MapStateToEvenIndex_020cd924(SeekerState *state);
extern void SoundRequest_Play_020cd9c0(SeekerState *state, VecFx32 *position);
extern void MarkList_AddAtObject_020cde4c(SeekerContext *context, Seeker *seeker);
extern int func_ov059_020ce3bc(SeekerContext *context, Seeker *seeker, VecFx32 *position, int flag);
extern void Seeker_SelectNearestTarget_020cec8c(Seeker *seeker, SeekerWorld *world);
extern void TargetKey_GetPosition_020cf0a4(VecFx32 *out, TargetRef *key);
extern BOOL IsTargetInVerticalRange_020cf100(TargetRef *ref);
extern int func_ov059_020cf394(void *list, TargetRef *key);
extern int func_ov059_020cec30();
extern void Body_ReflectVelocity_020cec3c();

static inline fx32 SafeDiv(fx32 numer, fx32 denom)
{
    if (denom != 0) {
        return FX_Div_01ff9c84(numer, denom);
    }
    return (numer == 0 ? 0 : numer > 0 ? 1 : -1) * 0x7fffffff * (denom >= 0 ? 1 : -1);
}

static inline BasisMatrix MakeBasis(const VecFx32 *forward, const VecFx32 *up)
{
    BasisMatrix result;
    BasisMatrix basis;

    BuildBasisMatrix_0204bf28(forward, up, &basis);
    *(BasisMatrix *)&result = *(BasisMatrix *)&basis;
    return result;
}

static inline VecFx32 ScaledVec(const VecFx32 *vec, fx32 scale)
{
    VecFx32 result = *vec;
    ScaleVecFx32InPlace_0204a5e4(&result, scale);
    return result;
}

static inline VecFx32 MultAddVec(fx32 scale, const VecFx32 *vec, const VecFx32 *add)
{
    VecFx32 result;
    VEC_MultAdd_01ffa09c(scale, vec, add, &result);
    return result;
}

int Seeker_Update_020cde6c(SeekerContext *context, Seeker *seeker, fx32 step)
{
    SweptShape sweptCopy;
    QueryWorkspace workspace;
    CollisionQuery sweep;
    SweptShape swept;
    CollisionQuery query;
    VecFx32 oldPos;
    VecFx32 dir;
    VecFx32 targetPos;
    VecFx32 delta;
    VecFx32 toTarget;
    VecFx32 toTargetDir;
    VecFx32 seekPos;
    VecFx32 seekDir;
    BasisMatrix basis;
    Sphere sphere;
    VecFx32 targetTemp;
    VecFx32 seekTemp;
    VecFx32 dirTemp;
    VecFx32 deltaTemp;
    VecFx32 unused;
    VecFx32 toTargetTemp;
    VecFx32 toTargetDirTemp;
    VecFx32 seekDirTemp;
    VecFx32 seekDeltaTemp;
    VecFx32 seekDelta;
    VecFx32 up;
    VecFx32 newPos;
    TargetRef none;
    QueryCallback filterCallback;
    QueryCallback contactCallback;
    SeekerState *state = seeker->state;
    int spin;
    VecFx32 *pos = &seeker->position;
    AnimSlot *anim;
    fx32 speed;
    fx32 accel;
    fx32 dot;
    fx32 angle;
    fx32 maxTurn;
    fx32 turn;
    fx32 boost;
    fx32 dist;
    fx32 spread;
    int pitch;
    int pitchIndex;
    int index;
    fx32 cosPitch;

    oldPos = *pos;
    if (state->pending) {
        func_ov059_020ce3bc(context, seeker, pos, 0);
        state->pending = 0;
    }
    switch (state->kind) {
    case 1:
        break;
    case 2:
        if (!IsTargetInVerticalRange_020cf100(&state->target)) {
            if (state->kind == 2) {
                state->kind = 1;
                state->flags &= ~4;
                state->timer = 0;
                state->interval = 0x1000;
                state->boostTime = 0xefed;
                state->boostDuration = 0xefed;
            }
            func_ov059_020cf394((u8 *)context->world + 0x15b4, &state->target);
            none.object = NULL;
            none.type = 0;
            state->target = none;
        } else {
            speed = VEC_Normalize_01ffaff4(&seeker->velocity, &dirTemp);
            dir = dirTemp;
            TargetKey_GetPosition_020cf0a4(&targetTemp, &state->target);
            targetPos = targetTemp;
            VEC_Subtract_01ff9e3c(&targetPos, &state->lastTargetPos, &deltaTemp);
            delta = deltaTemp;
            VEC_Normalize_01ffaff4(&delta, &unused);
            dot = VEC_DotProduct_01ff9e6c(&dir, &delta);
            accel = FixedPointMultiply12(0x333, step);
            if (dot > FixedPointMultiply12(speed, 0x800)) {
                speed += accel;
                VEC_Normalize_01ffaff4(&seeker->velocity, &seeker->velocity);
                ScaleVecFx32InPlace_0204a5e4(&seeker->velocity, speed);
            } else if (speed > state->baseSpeed + 0x10) {
                if (speed > state->baseSpeed + accel) {
                    speed -= accel;
                } else {
                    speed = state->baseSpeed;
                }
                VEC_Normalize_01ffaff4(&seeker->velocity, &seeker->velocity);
                ScaleVecFx32InPlace_0204a5e4(&seeker->velocity, speed);
            }
            state->lastTargetPos = targetPos;
            VEC_Subtract_01ff9e3c(&targetPos, pos, &toTargetTemp);
            toTarget = toTargetTemp;
            VEC_Normalize_01ffaff4(&toTarget, &toTargetDirTemp);
            toTargetDir = toTargetDirTemp;
            angle = ((s64)AngleBetweenVecs_0204b070(&dir, &toTargetDir) * 0x6488) / 0x10000;
            dot = VEC_DotProduct_01ff9e6c(&dir, &toTarget);
            if (dot < 0) {
                dot = 0;
            }
            maxTurn = angle > 0x861 ? 0x861 : angle;
            turn = FX_Sqrt_01ff9cfc(SafeDiv(angle, dot));
            turn = FixedPointMultiply12(turn, FixedPointMultiply12(speed, state->interval));
            if (turn > maxTurn) {
                turn = maxTurn;
            }
            if (state->boostDuration != 0) {
                boost = FX_Div_01ff9c84(state->boostTime, state->boostDuration);
            } else {
                boost = 0x1000;
            }
            RotateVecTowardVec_0204b0ac(&seeker->velocity, &toTargetDir,
                FixedPointMultiply12(FixedPointMultiply12(turn, FixedPointMultiply12(boost, state->timer)), step));
        }
        state->boostTime -= step;
        if (state->boostTime < 0) {
            state->boostTime = 0;
        }
        if (state->target.type == 0) {
            Seeker_SelectNearestTarget_020cec8c(seeker, context->world);
        }
        break;
    case 4:
        state->timer += 0x1000;
        if (state->timer >= state->interval) {
            state->timer -= state->interval;
            state->interval = random_next_scaled_0202aa04(0x9c6) + 0x5000;
            Seeker_SelectNearestTarget_020cec8c(seeker, context->world);
            if (state->target.type != 0) {
                TargetKey_GetPosition_020cf0a4(&seekTemp, &state->target);
                seekPos = seekTemp;
                VEC_Subtract_01ff9e3c(&seekPos, pos, &seekDeltaTemp);
                seekDelta = seekDeltaTemp;
                dist = VEC_Normalize_01ffaff4(&seekDelta, &seekDirTemp);
                seekDir = seekDirTemp;
                if (dist > 0x3000) {
                    spread = 0x10c1;
                } else {
                    spread = FixedPointMultiply12(0x10c1, FX_Div_01ff9c84(dist, 0x3000));
                }
                pitch = random_next_scaled_0202aa04(spread) + 0x1922;
                spin = random_next_scaled_0202aa04(0x6488);
                up = PickPerpendicularAxis_0204acb0(&seekDir);
                basis = MakeBasis(&seekDir, &up);
                pitchIndex = ANGLE_INDEX(pitch);
                cosPitch = COS_AT(pitchIndex);
                seeker->velocity = ScaledVec(&basis.row[2], FixedPointMultiply12(COS_AT(ANGLE_INDEX(spin)), cosPitch));
                VEC_MultAdd_01ffa09c(FixedPointMultiply12(SIN_AT(ANGLE_INDEX(spin)), cosPitch), &basis.row[1], &seeker->velocity, &seeker->velocity);
                VEC_MultAdd_01ffa09c(SIN_AT(pitchIndex), &basis.row[0], &seeker->velocity, &seeker->velocity);
                ScaleVecFx32InPlace_0204a5e4(&seeker->velocity, 0x99a);
            }
        }
        swept.shape = MakeSphereShape_0203ad14(&sphere, pos, seeker->def->radius);
        swept.delta = seeker->velocity;
        OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
        sweptCopy = swept;
        CollisionQuery_Init_02034c74(&query, 0, context->world->actor, 7, 0, 1, &sweptCopy, &workspace, NULL);
        sweep = query;
        filterCallback.func = (void *)func_ov059_020cec30;
        filterCallback.arg = NULL;
        sweep.filter = filterCallback;
        contactCallback.func = (void *)Body_ReflectVelocity_020cec3c;
        contactCallback.arg = seeker;
        sweep.callback = contactCallback;
        SweepWorldCollision_020364a0(&sweep);
        if (pos->y < 0) {
            MarkList_AddAtObject_020cde4c(context, seeker);
            SoundRequest_Play_020cd9c0(state, pos);
            seeker->status = -1;
            return 0;
        }
        break;
    }
    seeker->position = MultAddVec(step, &seeker->velocity, pos);
    index = MapStateToEvenIndex_020cd924(state);
    anim = index ? &context->slots[index] : (AnimSlot *)seeker->anim;
    state->animTime += step;
    if (state->animTime >= func_0202f4b8(anim, 0)) {
        state->animTime = 0;
    }
    return func_ov059_020ce3bc(context, seeker, &oldPos, 1);
}
