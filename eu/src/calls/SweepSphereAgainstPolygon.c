#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionEdge {
    VecFx32 vertex;
    VecFx32 direction;
    VecFx32 normal;
    u8 pad_24[0xc];
} CollisionEdge;

typedef struct CollisionPolygon {
    CollisionEdge edges[4];
    u8 edgeCount;
    u8 pad_c1[3];
    VecFx32 normal;
} CollisionPolygon;

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
extern fx32 FX_Sqrt(fx32 value);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void NormalizeIfShort(VecFx32 *vec);
extern void InitHitQuery(SweepResult *result);
extern BOOL SweepIntervalOnAxis(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity,
                                SweepResult *result, s64 *outTime);
extern BOOL ClipRayAgainstPlane(fx32 planeDist, fx32 startDist, const VecFx32 *normal, u8 id, const VecFx32 *direction,
                                SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern fx32 BlendVectorsBySqrtComplement(VecFx32 *a, const VecFx32 *b, fx32 t, s8 factor, VecFx32 *out);
extern fx32 NormalizeOrVerticalAxis(const VecFx32 *src, VecFx32 *dst, BOOL vertical);
extern VecFx32 GetNormalizedCross(const VecFx32 *vec, const VecFx32 *axis, BOOL verticalOnly);
extern VecFx32 ProjectPositionAtTimeMaybeVertical(s64 time, const VecFx32 *velocity, const VecFx32 *origin,
                                                  BOOL verticalOnly);
extern void ScaleVecFx32ComponentsConditional(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern VecFx32 AddScaledDirection(fx32 scale, const VecFx32 *direction, const VecFx32 *origin, BOOL verticalOnly);

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

static inline VecFx32 Cross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    VEC_CrossProduct(a, b, &cross);
    return cross;
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

static inline CollisionEdge *Polygon_GetEdge(CollisionPolygon *polygon, u8 index)
{
    return &polygon->edges[index];
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

static inline fx32 Sphere_GetRadius(const CollisionSphere *sphere)
{
    return sphere->radius;
}

/* Sphere moving by velocity against a polygon: the polygon's plane, then for every edge either the
 * edge's own normal (when both the motion and the polygon are vertical-only) or the plane through the
 * edge turned toward the sphere, and finally the corner the sphere slides onto. Some edge fields are
 * read through the edge array's base, as the ROM computes those addresses again instead of reusing
 * the edge pointer. */
BOOL SweepSphereAgainstPolygon(CollShape *sphereShape, CollShape *polygonShape, void *contact, u32 flags,
                               const VecFx32 *velocity)
{
    CollisionSphere *sphere = sphereShape->data;
    CollisionPolygon *polygon = polygonShape->data;
    SweepResult result = MakeSweepResult();
    VecFx32 axis;
    VecFx32 offset = VecSub(&sphere->center, &polygon->edges[0].vertex);
    s64 time;
    BOOL vertical;
    BOOL flat;
    BOOL bothVertical;
    u8 edgeCount;
    u8 i;

    axis = polygon->normal;
    if (!SweepIntervalOnAxis(Sphere_GetRadius(sphere), VEC_DotProduct(&axis, &offset), &axis, 0, velocity, &result,
                             NULL)) {
        return FALSE;
    }
    vertical = velocity->x == 0 && velocity->z == 0;
    flat = polygon->normal.x == 0 && polygon->normal.z == 0;
    bothVertical = vertical && flat;
    {
        const VecFx32 direction = MoveDirection(velocity, vertical);
        VecFx32 edgeNormal;
        VecFx32 side;
        VecFx32 point;

        edgeCount = polygon->edgeCount;
        for (i = 0; i < edgeCount; i++) {
            CollisionEdge *edge = Polygon_GetEdge(polygon, i);

            offset = VecSub(&sphere->center, &edge->vertex);
            if (!bothVertical) {
                s8 sign;
                fx32 along;
                fx32 distance;

                edgeNormal = EdgeNormal(&((CollisionEdge *)polygon + i)->direction, &direction, vertical);
                side = Cross(&edgeNormal, &((CollisionEdge *)polygon + i)->direction);
                sign = VEC_DotProduct(&side, &offset) >= 0 ? 1 : -1;
                along = VEC_DotProduct(&offset, &edgeNormal);
                distance = along < 0 ? -along : along;
                BlendVectorsBySqrtComplement(&edgeNormal, &side,
                                             Sign(along) * (distance < Sphere_GetRadius(sphere)
                                                                ? FX_Div(distance, Sphere_GetRadius(sphere))
                                                                : 0x1000),
                                             sign, &axis);
                if (VEC_DotProduct(&axis, &edge->normal) < 0) {
                    continue;
                }
            } else {
                if (VEC_DotProduct(&offset, &edge->normal) < 0) {
                    continue;
                }
                axis = ((CollisionEdge *)polygon + i)->normal;
            }
            if (!ClipRayAgainstPlane(Sphere_GetRadius(sphere), VEC_DotProduct(&axis, &offset), &axis, 1, velocity,
                                     &result, &time)) {
                return FALSE;
            }
            point = time > 0 ? ProjectPositionAtTimeMaybeVertical(time, velocity, &offset, vertical) : offset;
            if (VEC_DotProduct(&point, &axis) < 0) {
                continue;
            }
            if (VEC_DotProduct(&point, &edge->direction) > 0) {
                point = VecSub(&sphere->center, &polygon->edges[(i + 1) % edgeCount].vertex);
                if (time > 0) {
                    point = ProjectPositionAtTimeMaybeVertical(time, velocity, &point, vertical);
                }
                if (VEC_DotProduct(&point, &edge->direction) <= 0) {
                    continue;
                }
            }
            {
                const VecFx32 closest = RejectConditional(&point, &direction, VEC_DotProduct(&point, &direction), vertical);
                fx32 radiusSquared = FxMul(Sphere_GetRadius(sphere), Sphere_GetRadius(sphere));
                fx32 distanceSquared = VEC_DotProduct(&closest, &closest);
                fx32 back;

                if (radiusSquared < distanceSquared) {
                    if (VEC_DotProduct(&closest, &edge->normal) < 0) {
                        continue;
                    }
                    return FALSE;
                }
                back = -FX_Sqrt(radiusSquared - distanceSquared);
                axis = closest;
                axis = AddScaledDirection(back, &direction, &axis, vertical);
                NormalizeIfShort(&axis);
                if (!ClipRayAgainstPlane(Sphere_GetRadius(sphere), VEC_DotProduct(&axis, &point), &axis, 1, velocity,
                                         &result, NULL)) {
                    return FALSE;
                }
            }
        }
    }
    return ResolveSweepContact(&result, contact, flags, velocity);
}
