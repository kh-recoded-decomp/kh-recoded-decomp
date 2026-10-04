#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionCapsule {
    VecFx32 start;
    VecFx32 end;
    VecFx32 axis;
    fx32 length;
    fx32 radius;
    fx32 sine;
} CollisionCapsule;

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 GetObbProjectedRadius_0203d4d0(const void *box, const VecFx32 *axis);
extern fx32 GetCapsuleProjectedExtent_0203d684(const void *capsule, const VecFx32 *axis);
extern fx32 GetMaxProjectedSpread_0203d7f4(void *shape, const VecFx32 *axis);

static inline VecFx32 SegmentDelta(const CollisionCapsule *segment)
{
    VecFx32 delta;
    VEC_Subtract_01ff9e3c(&segment->end, &segment->start, &delta);
    return delta;
}

static inline VecFx32 HalveVec(VecFx32 vec)
{
    vec.x >>= 1;
    vec.y >>= 1;
    vec.z >>= 1;
    return vec;
}

static inline VecFx32 HalfSegment(const CollisionCapsule *segment)
{
    return HalveVec(SegmentDelta(segment));
}

static inline fx32 AbsFx32(fx32 value)
{
    return value < 0 ? -value : value;
}

static inline fx32 AbsProjection(VecFx32 vec, const VecFx32 *axis)
{
    return AbsFx32(VEC_DotProduct_01ff9e6c(&vec, axis));
}

fx32 GetShapeProjectedRadius_0203b2cc(const CollisionShape *shape, const VecFx32 *axis)
{
    switch (shape->kind) {
    case 0:
        return ((CollisionSphere *)shape->data)->radius;
    case 1:
        return GetObbProjectedRadius_0203d4d0(shape->data, axis);
    case 2: {
        VecFx32 half = SegmentDelta(shape->data);
        half.x >>= 1;
        half.y >>= 1;
        half.z >>= 1;
        return AbsProjection(half, axis);
    }
    case 3: {
        CollisionCapsule *capsule = shape->data;
        return capsule->radius + AbsProjection(HalfSegment(capsule), axis);
    }
    case 4:
        return GetCapsuleProjectedExtent_0203d684(shape->data, axis);
    case 5:
        return GetMaxProjectedSpread_0203d7f4(shape->data, axis);
    }
    return 0;
}
