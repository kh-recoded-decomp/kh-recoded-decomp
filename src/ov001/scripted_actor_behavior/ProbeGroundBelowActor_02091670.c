#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Surface {
    u8 pad_00[0x40];
    s32 kind;
} Surface;

typedef struct ActorBody {
    u8 pad_000[0x10c];
    Surface surface;
} ActorBody;

typedef struct ProbeActor {
    u8 pad_000[0x10];
    ActorBody body;
    u8 pad_160[0x2b4 - 0x160];
    fx32 stepHeight;
    u8 pad_2b8[0x2ee - 0x2b8];
    u16 raised : 1;
} ProbeActor;

typedef struct GroundQuery {
    VecFx32 *origin;
    VecFx32 *direction;
    fx32 radius;
    u16 flags;
    u16 mask;
    ActorBody *owner;
    u8 pad_14[0x4c];
} GroundQuery;

typedef struct GroundHit {
    u8 pad_00[4];
    void *surface;
    u8 pad_08[0x2c - 0x08];
    fx32 distance;
} GroundHit;

extern fx32 Surface_GetKindValue_02034c24(Surface *surface);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern GroundHit *QueryWorldModelCollision_02036468(GroundQuery *query);
extern void addScaledVector_020301ac(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

GroundHit *ProbeGroundBelowActor_02091670(ProbeActor *actor, const VecFx32 *from, const VecFx32 *to, VecFx32 *out, fx32 depth) {
    ActorBody *body = &actor->body;
    fx32 radius = 0x800;
    fx32 height;
    VecFx32 origin;
    VecFx32 direction;
    GroundQuery query;
    GroundHit *hit;

    if (body->surface.kind != -1) {
        radius = Surface_GetKindValue_02034c24(&body->surface) >> 1;
    }
    height = actor->stepHeight + radius;
    if (height < 0x1000) {
        height = 0x1000;
    }
    SetVec(&origin, from->x, from->y + height, from->z);
    if (to != NULL) {
        SetVec(&origin, to->x, origin.y, to->z);
        VEC_Subtract_01ff9e3c(to, from, &direction);
        func_01ffaff4(&direction, &direction);
        SetVec(&direction, FixedPointMultiply12(direction.x, depth), FixedPointMultiply12(direction.y, depth), FixedPointMultiply12(direction.z, depth));
    }
    if (actor->raised) {
        origin.y += 0x2000;
    }
    SetVec(&direction, 0, -(height + depth), 0);
    query.origin = &origin;
    query.direction = &direction;
    query.radius = radius;
    query.flags = 0;
    query.mask = 0xcf;
    query.owner = &actor->body;
    hit = QueryWorldModelCollision_02036468(&query);
    if (hit != NULL && hit->surface != NULL) {
        addScaledVector_020301ac(hit->distance, &direction, &origin, out);
        out->y -= radius;
        return hit;
    }
    *out = *from;
    out->y = -0x3000;
    return NULL;
}
