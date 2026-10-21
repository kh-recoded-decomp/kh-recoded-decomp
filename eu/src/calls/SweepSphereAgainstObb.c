#pragma opt_loop_invariants off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} CollisionBox;

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
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void InitHitQuery(SweepResult *result);
extern BOOL SweepIntervalOnAxis(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity,
                                SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern fx32 BlendVectorsBySqrtComplement(VecFx32 *a, const VecFx32 *b, fx32 t, s8 factor, VecFx32 *out);
extern fx32 ComputeOneMinusSquareFraction(fx32 t);
extern fx32 NormalizeOrVerticalAxis(const VecFx32 *src, VecFx32 *dst, BOOL vertical);
extern VecFx32 GetNormalizedCross(const VecFx32 *vec, const VecFx32 *axis, BOOL verticalOnly);
extern void ScaleVecFx32ComponentsConditional(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern void NegateVecComponentsConditional(VecFx32 *vec, s32 sign, s32 skipHorizontal);
extern VecFx32 AddScaledDirection(fx32 scale, const VecFx32 *direction, const VecFx32 *origin, BOOL verticalOnly);
extern fx32 GetObbProjectedRadius(const CollisionBox *box, const VecFx32 *axis);
extern void GetBoxEdgeDiagonal(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out);
extern void GetBoxEdgeMidpointOffset(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out);
extern void GetBoxLocalPoint(const CollisionBox *box, fx32 x, fx32 y, fx32 z, VecFx32 *out);

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

static inline VecFx32 MoveDirection(const VecFx32 *velocity, BOOL vertical)
{
    VecFx32 direction;
    NormalizeOrVerticalAxis(velocity, &direction, vertical);
    return direction;
}

static inline VecFx32 EdgeNormal(const VecFx32 *edgeDirection, const VecFx32 *direction, BOOL vertical)
{
    VecFx32 normal;

    normal = GetNormalizedCross(edgeDirection, direction, vertical);
    return normal;
}

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

/* The cross product with the box axis, written out for the up axis of an upright box. */
static inline VecFx32 EdgeSide(const VecFx32 *normal, const VecFx32 *axis, BOOL upAxis)
{
    VecFx32 side;

    if (!upAxis) {
        VEC_CrossProduct(normal, axis, &side);
    } else {
        side.x = -FxMul(normal->z, axis->y);
        side.y = 0;
        side.z = FxMul(normal->x, axis->y);
    }
    return side;
}

static inline VecFx32 EdgeDiagonal(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge)
{
    VecFx32 diagonal;
    GetBoxEdgeDiagonal(box, axisA, axisB, edge, &diagonal);
    return diagonal;
}

static inline VecFx32 EdgeMidpoint(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge)
{
    VecFx32 midpoint;
    GetBoxEdgeMidpointOffset(box, axisA, axisB, edge, &midpoint);
    return midpoint;
}

static inline VecFx32 BoxCorner(const CollisionBox *box, fx32 x, fx32 y, fx32 z)
{
    VecFx32 corner;
    GetBoxLocalPoint(box, x, y, z, &corner);
    return corner;
}

static inline void SubtractVecConditional(VecFx32 *vec, const VecFx32 *offset, BOOL vertical)
{
    if (!vertical) {
        vec->x -= offset->x;
        vec->z -= offset->z;
    }
    vec->y -= offset->y;
}

static inline VecFx32 RejectConditional(const VecFx32 *vec, const VecFx32 *axis, fx32 amount, BOOL vertical)
{
    VecFx32 offset;
    VecFx32 projected;
    VecFx32 rejection;
    VecFx32 *offsetPtr;

    projected = *axis;
    ScaleVecFx32ComponentsConditional(&projected, amount, vertical);
    offsetPtr = &offset;
    *offsetPtr = projected;
    rejection = *vec;
    SubtractVecConditional(&rejection, offsetPtr, vertical);
    return rejection;
}

static inline VecFx32 NegatedConditional(VecFx32 v, s32 sign, BOOL vertical)
{
    NegateVecComponentsConditional(&v, sign, vertical);
    return v;
}

static inline VecFx32 Normalized(const VecFx32 *v)
{
    VecFx32 unit;
    VEC_Normalize(v, &unit);
    return unit;
}

static inline VecFx32 Scaled(const VecFx32 *v, fx32 scale)
{
    VecFx32 scaled = *v;
    ScaleVecFx32InPlace(&scaled, scale);
    return scaled;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

static inline fx32 Sphere_GetRadius(const CollisionSphere *sphere)
{
    return sphere->radius;
}

/* Sphere moving by velocity against an oriented box. An upright box hit from straight above or
 * below inside its footprint only needs its up axis; otherwise the sweep runs over the three box
 * axes, the planes through each box edge turned toward the sphere, and the directions to the
 * eight corners. */
BOOL SweepSphereAgainstObb(CollShape *sphereShape, CollShape *boxShape, void *contact, u32 flags,
                           const VecFx32 *velocity)
{
    CollisionSphere *sphere = sphereShape->data;
    CollisionBox *box = boxShape->data;
    BOOL vertical = velocity->x == 0 && velocity->z == 0;
    BOOL upright = box->flags & 1;
    BOOL straightDown = vertical && upright;
    SweepResult result = MakeSweepResult();
    VecFx32 offset = VecSub(&sphere->center, &box->center);
    VecFx32 axis;
    s8 i;
    s8 j;
    s8 edge;
    s32 axisA;
    s32 axisB;
    BOOL upAxis;
    fx32 along;
    s8 x;
    s8 y;
    s8 z;

    if (straightDown && (offset.x < 0 ? -offset.x : offset.x) < box->halfExtents[0] &&
        (offset.z < 0 ? -offset.z : offset.z) < box->halfExtents[2]) {
        fx32 extent = box->halfExtents[1] + Sphere_GetRadius(sphere);

        if (!SweepIntervalOnAxis(extent, VEC_DotProduct(&box->axes[1], &offset), &box->axes[1], 0, velocity, &result,
                                 NULL)) {
            return FALSE;
        }
    } else {
        const VecFx32 direction = MoveDirection(velocity, vertical);
        VecFx32 edgeNormal;
        VecFx32 side;
        VecFx32 diagonal;
        VecFx32 midpoint;
        VecFx32 corner;

        for (i = 0; i < 3; i++) {
            fx32 extent;

            axis = box->axes[i];
            extent = box->halfExtents[i] + Sphere_GetRadius(sphere);
            if (!SweepIntervalOnAxis(extent, VEC_DotProduct(&axis, &offset), &axis, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
        for (j = 0; j < 3; j++) {
            axisA = (s8)((j + 1) % 3);
            axisB = (s8)((j + 2) % 3);
            upAxis = FALSE;
            if (upright && j == 1) {
                upAxis = TRUE;
            }
            edgeNormal = EdgeNormal(&box->axes[j], &direction, vertical);
            side = EdgeSide(&edgeNormal, &box->axes[j], upAxis);
            along = VEC_DotProduct(&edgeNormal, &offset);
            edge = 0;
            for (; edge < 4; edge++) {
                fx32 distance;
                fx32 extent;

                diagonal = EdgeDiagonal(box, axisA, axisB, edge);
                if (VEC_DotProduct(&diagonal, &direction) > 0xb50) {
                    continue;
                }
                midpoint = EdgeMidpoint(box, axisA, axisB, edge);
                distance = along - VEC_DotProduct(&midpoint, &edgeNormal);
                if (distance < 0) {
                    distance = -distance;
                }
                BlendVectorsBySqrtComplement(&edgeNormal, &side,
                                             Sign(along) * (distance < Sphere_GetRadius(sphere)
                                                                ? FX_Div(distance, Sphere_GetRadius(sphere))
                                                                : 0x1000),
                                             -1, &axis);
                VEC_Normalize(&axis, &axis);
                extent = GetObbProjectedRadius(box, &axis);
                extent += Sphere_GetRadius(sphere);
                if (!SweepIntervalOnAxis(extent, VEC_DotProduct(&axis, &offset), &axis, 1, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
        for (x = -1; x <= 1; x += 2) {
            for (y = -1; y <= 1; y += 2) {
                for (z = -1; z <= 1; z += 2) {
                    fx32 cornerAlong;
                    fx32 t;
                    fx32 rest;
                    fx32 extent;

                    corner = BoxCorner(box, x, y, z);
                    {
                        const VecFx32 toCorner = VecSub(&offset, &corner);
                        VecFx32 rejection;

                        cornerAlong = VEC_DotProduct(&toCorner, &direction);
                        rejection = RejectConditional(&toCorner, &direction, cornerAlong, vertical);
                        t = VEC_Mag(&rejection);
                        if (t < 0x10) {
                            axis = NegatedConditional(direction, cornerAlong, vertical);
                        } else {
                            t = t < Sphere_GetRadius(sphere) ? FX_Div(t, Sphere_GetRadius(sphere)) : 0x1000;
                            rest = t < 0x1000 ? ComputeOneMinusSquareFraction(t) : 0;
                            {
                                VecFx32 unit = Normalized(&rejection);

                                axis = Scaled(&unit, t);
                            }
                            if (rest != 0) {
                                axis = AddScaledDirection(rest * Sign(cornerAlong), &direction, &axis, vertical);
                            }
                            VEC_Normalize(&axis, &axis);
                        }
                    }
                    extent = GetObbProjectedRadius(box, &axis);
                    extent += Sphere_GetRadius(sphere);
                    if (!SweepIntervalOnAxis(extent, VEC_DotProduct(&axis, &offset), &axis, 1, velocity, &result,
                                             NULL)) {
                        return FALSE;
                    }
                }
            }
        }
    }
    return ResolveSweepContact(&result, contact, flags, velocity);
}
