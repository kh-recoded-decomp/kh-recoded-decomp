#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct CollisionCylinder {
    CollisionSegment axis;
    fx32 radius;
} CollisionCylinder;

typedef struct CollBox {
    fx32 maxX;
    fx32 maxY;
    fx32 maxZ;
    fx32 minX;
    fx32 minY;
    fx32 minZ;
} CollBox;

typedef struct CollShape {
    void *data;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct SweepResult {
    u32 enterTimeLo;
    s32 enterTimeHi;
    u32 exitTimeLo;
    s32 exitTimeHi;
    VecFx32 enterAxis;
    fx32 minDepth;
    VecFx32 depthAxis;
    s8 depthSign;
    u8 depthFeature;
    u8 pad_2E[2];
    s8 enterSign;
    u8 touching;
    u8 enterFeature;
    u8 pad_33;
} SweepResult;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void NegateVecFx32(VecFx32 *vec);
extern void NormalizeIfShort(VecFx32 *vec);
extern void InitHitQuery(SweepResult *result);
extern BOOL TestSegmentAgainstSphere(CollShape *segmentShape, CollShape *sphereShape, void *contact, BOOL resolve);
extern BOOL SweepIntervalOnAxis(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity,
                                SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void GetUnitCross(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern fx32 BlendVectorsBySqrtComplement(VecFx32 *a, const VecFx32 *b, fx32 t, s8 factor, VecFx32 *out);
extern VecFx32 AverageVecs(s32 count, ...);
extern fx32 ComputeOneMinusSquareFraction(fx32 t);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    InitHitQuery(&result);
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract(a, b, &diff);
    return diff;
}

static inline VecFx32 UnitVector(const VecFx32 *v)
{
    VecFx32 unit = *v;
    NormalizeIfShort(&unit);
    return unit;
}

static inline VecFx32 PerpAxis(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 perp;
    GetUnitCross(&perp, a, b);
    return perp;
}

static inline VecFx32 Cross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    VEC_CrossProduct(a, b, &cross);
    return cross;
}

static inline VecFx32 Scaled(const VecFx32 *v, fx32 scale)
{
    VecFx32 scaled = *v;
    ScaleVecFx32InPlace(&scaled, scale);
    return scaled;
}

static inline VecFx32 Normalized(const VecFx32 *v)
{
    VecFx32 unit;
    VEC_Normalize(v, &unit);
    return unit;
}

static inline VecFx32 Negated(const VecFx32 *v)
{
    VecFx32 negated = *v;
    NegateVecFx32(&negated);
    return negated;
}

static inline VecFx32 MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_MultAdd(scale, a, b, &sum);
    return sum;
}

static inline VecFx32 FacingSign(VecFx32 v, fx32 side)
{
    if (side < 0) {
        NegateVecFx32(&v);
    }
    return v;
}

static inline VecFx32 VecSum(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add(a, b, &sum);
    return sum;
}

static inline VecFx32 RejectAlong(const VecFx32 *vec, const VecFx32 *axis, fx32 amount)
{
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;

    scaledAxis = *axis;
    ScaleVecFx32InPlace(&scaledAxis, amount);
    projection = scaledAxis;
    VEC_Subtract(vec, &projection, &rejection);
    return rejection;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

static inline fx32 FxMul64(fx32 a, fx64 b)
{
    return (fx32)(((fx64)a * b + 0x800) >> 12);
}

static inline fx32 Sphere_GetRadius(const CollisionSphere *sphere)
{
    return sphere->radius;
}

/* Sphere moving by velocity against a cylinder's axis; callers inflate the sphere by the cylinder
 * radius. Without flags & 8 the motion is folded into the axis (stretched back by the velocity) and
 * tested as a segment against the still sphere. Otherwise it sweeps along the separating axes: the
 * blend between the axis's side and perpendicular directions, then one axis per axis end. */
BOOL SweepSphereAgainstCylinder(CollShape *sphereShape, CollShape *cylinderShape, void *contact, u32 flags,
                                const VecFx32 *velocity)
{
    CollisionSphere *sphere = sphereShape->data;
    CollisionCylinder *cylinder = cylinderShape->data;

    if (!(flags & 8)) {
        CollShape pathShape;
        CollisionSegment path = cylinder->axis;

        path.end = VecSum(&path.end, &Negated(velocity));
        pathShape.data = &path;
        return TestSegmentAgainstSphere(&pathShape, sphereShape, contact, ~flags & 1);
    } else {
        SweepResult result = MakeSweepResult();
        VecFx32 normal;
        VecFx32 center = AverageVecs(2, &cylinder->axis.start, &cylinder->axis.end);
        VecFx32 diff = VecSub(&sphere->center, &center);
        VecFx32 axis = cylinder->axis.direction;
        fx32 length = cylinder->axis.length;
        const VecFx32 dir = UnitVector(velocity);
        VecFx32 side = PerpAxis(&axis, &dir);
        VecFx32 perp = Cross(&side, &axis);
        VecFx32 toEnd;
        VecFx32 rejection;
        fx32 sideDot;
        fx32 sideDistance;
        fx32 weight;
        fx32 t;
        fx32 rest;
        fx32 extent;
        s8 i;
        int flip = -1;
        fx32 along;

        sideDot = VEC_DotProduct(&diff, &side);
        sideDistance = sideDot < 0 ? -sideDot : sideDot;
        weight = Sign(sideDot) *
                 (sideDistance < Sphere_GetRadius(sphere) ? FX_Div(sideDistance, Sphere_GetRadius(sphere)) : 0x1000);
        BlendVectorsBySqrtComplement(&side, &perp, weight, flip, &normal);
        if (!SweepIntervalOnAxis(Sphere_GetRadius(sphere), VEC_DotProduct(&normal, &diff), &normal, 1, velocity, &result,
                                 NULL)) {
            return FALSE;
        }
        for (i = 0; i < 2; i++) {
            toEnd = VecSub(&sphere->center, i == 0 ? &cylinder->axis.start : &cylinder->axis.end);
            along = VEC_DotProduct(&toEnd, &dir);
            rejection = RejectAlong(&toEnd, &dir, along);
            t = VEC_Mag(&rejection);
            if (t < 0x10) {
                normal = FacingSign(dir, along);
            } else {
                t = t < Sphere_GetRadius(sphere) ? FX_Div(t, Sphere_GetRadius(sphere)) : 0x1000;
                rest = t < 0x1000 ? ComputeOneMinusSquareFraction(t) : 0;
                {
                    VecFx32 unit = Normalized(&rejection);

                    normal = Scaled(&unit, t);
                }
                if (rest != 0) {
                    normal = MultAdd(rest * (along >= 0 ? 1 : flip), &dir, &normal);
                }
                VEC_Normalize(&normal, &normal);
            }
            extent = FxMul64(AbsDotProduct(&axis, &normal), length / 2) + Sphere_GetRadius(sphere);
            if (!SweepIntervalOnAxis(extent, VEC_DotProduct(&normal, &diff), &normal, 1, velocity, &result, NULL)) {
                return FALSE;
            }
        }
        return ResolveSweepContact(&result, contact, flags, velocity);
    }
}
