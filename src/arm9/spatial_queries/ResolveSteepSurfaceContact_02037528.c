#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Surface {
    u8 pad_00[0x40];
    s32 unk_40;
} Surface;

typedef struct SurfaceRef {
    Surface *surface;
    s32 kind;
    u8 flags;
} SurfaceRef;

typedef struct ContactPlane {
    s32 distance;
    VecFx32 normal;
    s32 time;
    u8 surfaceType;
} ContactPlane;

typedef struct Body {
    u32 pad_00;
    u32 flags;
    u8 pad_08[0x0c];
    VecFx32 push;
    VecFx32 velocity;
    s32 unk_2C;
} Body;

typedef struct ContactState {
    Body *body;
    VecFx32 *expected;
    u8 pad_08[0x28];
    u32 flags;
} ContactState;

typedef struct CollSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollSegment;

typedef struct Capsule {
    CollSegment segment;
    fx32 radius;
} Capsule;

typedef struct CollShape {
    Capsule *capsule;
    fx32 box[6];
    s32 kind;
} CollShape;

typedef struct Mover {
    CollShape shape;
    VecFx32 velocity;
} Mover;

typedef struct StageEntry {
    u8 pad_00[0x9c0];
    s32 unk_9C0;
} StageEntry;

typedef struct Actor {
    u8 pad_00[0x180];
    u8 unk_180;
} Actor;

typedef struct PlanarVec {
    fx32 x;
    fx32 z;
} PlanarVec;

extern s16 data_020537ec[];
extern s16 data_020539ac[];
extern s16 data_0205362c[];

extern s32 func_ov001_02063a38(void);
extern StageEntry *GetBoundedEntryField_0206db5c(int index);
extern BOOL func_0203719c(Actor *actor, s32 limit);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 func_01ff9cfc(u32 value);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void func_0204a3e4(PlanarVec *vec);
extern void func_0204a420(PlanarVec *vec);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern void ScalePairInPlace_0204a350(PlanarVec *pair, fx32 scale);
extern fx32 func_02034c24(Surface *surface);
extern s64 Mul64_02023d9c(s64 a, s64 b);
extern fx32 FixedPointMultiply12(fx32 left, fx32 right);
extern void func_0203b1f0(CollSegment *segment);
extern void func_0203afa0(CollShape *shape, const VecFx32 *pos);
extern BOOL func_0203079c(CollShape *shape, SurfaceRef *ref, ContactPlane *contact);

static inline s32 Clamp(s32 value, s32 lo, s32 hi)
{
    return value > hi ? hi : (value < lo ? lo : value);
}

static inline BOOL IsMode7(void)
{
    return func_ov001_02063a38() == 7;
}

static inline VecFx32 CrossUp(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    cross.x = -(fx32)((Mul64_02023d9c(a->z, b->y) + 0x800) >> 12);
    cross.y = 0;
    cross.z = (fx32)((Mul64_02023d9c(a->x, b->y) + 0x800) >> 12);
    return cross;
}

static inline VecFx32 VecCross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct_01ff9ea8(a, b, &result);
    return result;
}

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Add_01ff9e0c(a, b, &result);
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

static inline void PlaceShape(CollShape *shape, VecFx32 pos)
{
    func_0203afa0(shape, &pos);
}

static inline PlanarVec GetPlanar(const VecFx32 *v)
{
    PlanarVec result;
    result.x = v->x;
    result.z = v->z;
    return result;
}

void ResolveSteepSurfaceContact_02037528(SurfaceRef *ref, VecFx32 *normal, ContactState *state, Actor *actor,
                                         Mover *mover)
{
    VecFx32 tangent;
    ContactPlane contact;
    CollShape shape;
    Capsule capsule;
    VecFx32 upAxis;
    PlanarVec slopeDir;
    PlanarVec pushDir;
    Body *body;
    fx32 speed;
    fx32 pushMag;
    s32 stageKind;

    if (ref->flags & 3) {
        body = state->body;
        if (state->expected->z != 0) {
            return;
        }
        if (mover->velocity.y <= 0 && !IsMode7() && body->velocity.x == 0 && body->velocity.y == 0 &&
            body->velocity.z == 0) {
            stageKind = GetBoundedEntryField_0206db5c(0)->unk_9C0;
            if ((state->flags & 4) == 0 &&
                ((stageKind >= 2 && stageKind <= 4) || (stageKind >= 10 && stageKind <= 13) ||
                 (stageKind >= 21 && stageKind <= 22) || (stageKind >= 25 && stageKind <= 27)) &&
                normal->y > 0 && (ref->flags & 3) && actor->unk_180 >= 2) {
                s32 limit;
                if (ref->kind == 4 && (ref->surface->unk_40 == 0 || ref->surface->unk_40 == 3)) {
                    limit = 0x10;
                } else {
                    limit = data_020537ec[0x15];
                }
                if (func_0203719c(actor, limit)) {
                    upAxis = MakeVec(0, 0x1000, 0);
                    tangent = CrossUp(normal, &upAxis);
                    body->velocity = VecCross(&tangent, normal);
                    body->velocity.y = Clamp(body->velocity.y, data_0205362c[0x11], data_020539ac[0x18]);
                    slopeDir = GetPlanar(&body->velocity);
                    func_0204a3e4(&slopeDir);
                    ScalePairInPlace_0204a350(&slopeDir,
                                              ComputeOneMinusSquareFraction_02049d6c(body->velocity.y));
                    body->velocity.x = slopeDir.x;
                    body->velocity.z = slopeDir.z;
                    if (ref->kind == 4 && ref->surface->unk_40 != 1) {
                        speed = FixedPointMultiply12(func_02034c24(ref->surface), 0x1333);
                        speed = Clamp(speed, 0x4cd, 0x666);
                        func_01ffaff4(&body->velocity, &body->velocity);
                        func_0204a5e4(&body->velocity, speed);
                    } else {
                        func_01ffaff4(&body->velocity, &body->velocity);
                        func_0204a5e4(&body->velocity, 0x4cd);
                    }
                    body->unk_2C = 0;
                    return;
                }
            }

            shape = mover->shape;
            capsule = *mover->shape.capsule;
            shape.capsule = &capsule;
            capsule.segment.start.y += 0x28000;
            capsule.segment.end.y -= 0x28000;
            func_0203b1f0(&capsule.segment);
            PlaceShape(&shape, VecAdd(&shape.capsule->segment.start, &mover->velocity));
            if (func_0203079c(&shape, ref, &contact)) {
                s64 zz;
                s64 xx;
                fx32 horizontalLen;

                pushDir = GetPlanar(&contact.normal);
                func_0204a420(&pushDir);
                pushMag = VEC_Mag_01ff9f28(&body->push);
                zz = normal->z;
                xx = normal->x;
                horizontalLen =
                    func_01ff9cfc((u32)((Mul64_02023d9c(xx, xx) + Mul64_02023d9c(zz, zz)) >> 12));
                if (horizontalLen < 0x800) {
                    horizontalLen = 0x800;
                }
                speed = FixedPointMultiply12(0x200, 0x1000 - horizontalLen);
                body->push.x += FixedPointMultiply12(pushDir.x, speed);
                body->push.z += FixedPointMultiply12(pushDir.z, speed);
                if (pushMag != 0) {
                    if (pushMag < speed) {
                        pushMag = speed;
                    }
                    func_01ffaff4(&body->push, &body->push);
                    func_0204a5e4(&body->push, pushMag);
                }
                body->flags |= 0x80;
            }
        }
    }
}
