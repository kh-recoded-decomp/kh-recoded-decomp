#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

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

typedef struct SweepResult {
    s64 enterTime;
    s64 exitTime;
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

extern int FX_Div_01ff9c84(int numer, int denom);
extern int FX_Sqrt_01ff9cfc(int value);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL ClipRayAgainstPlane_01fff6c8(fx32 planeDist, fx32 startDist, const VecFx32 *normal, u8 id,
                                         const VecFx32 *direction, SweepResult *result, s64 *outT);
extern void InitHitQuery_0203ac24(SweepResult *query);
extern BOOL SweepIntervalOnAxis_0204774c(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature,
                                         const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern fx32 NormalizeIfShort_0204a9b4(VecFx32 *vec);
extern fx32 BlendVectorsBySqrtComplement_0204b59c(VecFx32 *a, const VecFx32 *b, fx32 t, s32 factor, VecFx32 *out);
extern void ScaleVecFx32ComponentsConditional_0204b6c4(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern VecFx32 ProjectPositionAtTimeMaybeVertical_0204b790(s64 time, const VecFx32 *velocity, const VecFx32 *origin, BOOL verticalOnly);
extern VecFx32 AddScaledDirection_0204b834(fx32 scale, const VecFx32 *direction, const VecFx32 *origin, BOOL verticalOnly);
extern fx32 NormalizeOrVerticalAxis_0204b8bc(const VecFx32 *src, VecFx32 *dst, BOOL vertical);
extern VecFx32 GetNormalizedCross_0204b9c8(const VecFx32 *vec, const VecFx32 *axis, BOOL verticalOnly);

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    InitHitQuery_0203ac24(&result);
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract_01ff9e3c(a, b, &diff);
    return diff;
}

static inline VecFx32 NormalizedDirection(const VecFx32 *v, BOOL vertical)
{
    VecFx32 dir;
    NormalizeOrVerticalAxis_0204b8bc(v, &dir, vertical);
    return dir;
}

static inline void SubtractVecConditional(VecFx32 *vec, const VecFx32 *offset, BOOL vertical)
{
    if (!vertical) {
        vec->x -= offset->x;
        vec->z -= offset->z;
    }
    vec->y -= offset->y;
}

static inline VecFx32 RemoveAlong(const VecFx32 *vec, const VecFx32 *axis, fx32 along, BOOL vertical)
{
    VecFx32 offset;
    VecFx32 projected;
    VecFx32 rejection;
    VecFx32 *offsetPtr;

    projected = *axis;
    ScaleVecFx32ComponentsConditional_0204b6c4(&projected, along, vertical);
    offsetPtr = &offset;
    *offsetPtr = projected;
    rejection = *vec;
    SubtractVecConditional(&rejection, offsetPtr, vertical);
    return rejection;
}

static inline void EdgeBasis(VecFx32 *cross, VecFx32 *perp, const CollisionEdge *edgeRef, const VecFx32 *dir, BOOL vertical)
{
    VecFx32 product;

    *cross = GetNormalizedCross_0204b9c8(&edgeRef->direction, dir, vertical);
    VEC_CrossProduct_01ff9ea8(cross, &edgeRef->direction, &product);
    *perp = product;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

BOOL SweepSphereAgainstPolygon_02042f54(Sphere **sphereRef, CollisionPolygon **polygonRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    Sphere *sphere = *sphereRef;
    CollisionPolygon *polygon = *polygonRef;
    SweepResult result;
    VecFx32 axis;
    VecFx32 offset;
    VecFx32 dir;
    VecFx32 cross;
    VecFx32 perp;
    VecFx32 closest;
    VecFx32 planar;
    VecFx32 rejected;
    u8 i;
    s8 side;
    const VecFx32 *dirRef;
    s64 time;
    fx32 along;
    fx32 blend;
    fx32 radiusSq;
    fx32 distSq;
    BOOL verticalOnly;
    BOOL flatPolygon;
    BOOL useVertical;
    u8 edgeCount;
    fx32 radius;

    result = MakeSweepResult();
    offset = VecSub(&sphere->center, &polygon->edges[0].vertex);
    axis = polygon->normal;
    radius = sphere->radius;
    if (!SweepIntervalOnAxis_0204774c(radius, VEC_DotProduct_01ff9e6c(&axis, &offset), &axis, 0, velocity, &result, NULL)) {
        return FALSE;
    }
    verticalOnly = FALSE;
    if (velocity->x == 0 && velocity->z == 0) {
        verticalOnly = TRUE;
    }
    flatPolygon = FALSE;
    if (polygon->normal.x == 0 && polygon->normal.z == 0) {
        flatPolygon = TRUE;
    }
    useVertical = FALSE;
    if (verticalOnly && flatPolygon) {
        useVertical = TRUE;
    }
    dirRef = &NormalizedDirection(velocity, verticalOnly);
    dir = *dirRef;
    edgeCount = polygon->edgeCount;
    for (i = 0; i < edgeCount; i++) {
        offset = VecSub(&sphere->center, &polygon->edges[i].vertex);
        if (!useVertical) {
            EdgeBasis(&cross, &perp, &polygon->edges[i], &dir, verticalOnly);
            side = VEC_DotProduct_01ff9e6c(&perp, &offset) >= 0 ? 1 : -1;
            along = VEC_DotProduct_01ff9e6c(&offset, &cross);
            blend = along < 0 ? -along : along;
            BlendVectorsBySqrtComplement_0204b59c(&cross, &perp, Sign(along) * (blend < sphere->radius ? FX_Div_01ff9c84(blend, sphere->radius) : 0x1000), side, &axis);
            if (VEC_DotProduct_01ff9e6c(&axis, &polygon->edges[i].normal) < 0) {
                continue;
            }
        } else {
            if (VEC_DotProduct_01ff9e6c(&offset, &polygon->edges[i].normal) < 0) {
                continue;
            }
            axis = ((CollisionEdge *)polygon + i)->normal;
        }
        radius = sphere->radius;
        if (!ClipRayAgainstPlane_01fff6c8(radius, VEC_DotProduct_01ff9e6c(&axis, &offset), &axis, 1, velocity, &result, &time)) {
            return FALSE;
        }
        closest = time > 0 ? ProjectPositionAtTimeMaybeVertical_0204b790(time, velocity, &offset, verticalOnly) : offset;
        if (VEC_DotProduct_01ff9e6c(&closest, &axis) < 0) {
            continue;
        }
        if (VEC_DotProduct_01ff9e6c(&closest, &polygon->edges[i].direction) > 0) {
            closest = VecSub(&sphere->center, &polygon->edges[(i + 1) % edgeCount].vertex);
            if (time > 0) {
                closest = ProjectPositionAtTimeMaybeVertical_0204b790(time, velocity, &closest, verticalOnly);
            }
            if (VEC_DotProduct_01ff9e6c(&closest, &polygon->edges[i].direction) <= 0) {
                continue;
            }
        }
        along = VEC_DotProduct_01ff9e6c(&closest, &dir);
        rejected = RemoveAlong(&closest, dirRef, along, verticalOnly);
        planar = rejected;
        radiusSq = (fx32)(((s64)sphere->radius * sphere->radius + 0x800) >> 12);
        distSq = VEC_DotProduct_01ff9e6c(&planar, &planar);
        if (radiusSq < distSq) {
            if (VEC_DotProduct_01ff9e6c(&planar, &polygon->edges[i].normal) < 0) {
                continue;
            }
            return FALSE;
        }
        blend = -FX_Sqrt_01ff9cfc(radiusSq - distSq);
        axis = rejected;
        axis = AddScaledDirection_0204b834(blend, &dir, &axis, verticalOnly);
        NormalizeIfShort_0204a9b4(&axis);
        radius = sphere->radius;
        if (!ClipRayAgainstPlane_01fff6c8(radius, VEC_DotProduct_01ff9e6c(&axis, &closest), &axis, 1, velocity, &result, NULL)) {
            return FALSE;
        }
    }
    return ResolveSweepContact_0204792c(&result, contact, flags, velocity);
}
