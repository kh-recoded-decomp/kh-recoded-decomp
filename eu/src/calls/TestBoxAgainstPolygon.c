#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrientedBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} OrientedBox;

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

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

extern void InitMaxDistanceHit(PenetrationResult *result);
extern void SubtractVecFx32Into(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern fx32 GetObbProjectedRadius(const OrientedBox *box, const VecFx32 *axis);
extern BOOL TestSignedSeparatingAxis(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 featureId,
                          PenetrationResult *result);
extern fx32 GetProjectedInterval(CollisionPolygon *shape, const VecFx32 *axis, fx32 *center);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL UpdateSignedPenetrationDepth(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId,
                                         PenetrationResult *result);
extern void NegateVecFx32Into(VecFx32 *out, const VecFx32 *v);
extern BOOL GetCrossIfNonParallel(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void NormalizeIfShort(VecFx32 *v);
extern fx32 FlipVectorIfDotNegative(VecFx32 *a, const VecFx32 *b);
/* The caller passes the axis index as a u8. */
extern fx32 ProjectObbExtentExcludingAxis(OrientedBox *box, const VecFx32 *direction, u8 excludedAxis);
extern BOOL TestSeparatingAxis(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 featureId,
                          PenetrationResult *result);
extern void WritePenetrationContact(const PenetrationResult *result, void *contact, u32 flags);

static inline PenetrationResult MakePenetrationResult(void)
{
    PenetrationResult result;
    InitMaxDistanceHit(&result);
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    SubtractVecFx32Into(&diff, a, b);
    return diff;
}

/* Separating-axis test of an oriented box against a polygon: the polygon normal, the box
 * axes, then each box axis crossed with each polygon edge. */
BOOL TestBoxAgainstPolygon(OrientedBox **boxRef, CollisionPolygon **polygonRef, void *contact, u32 flags)
{
    OrientedBox *box = *boxRef;
    CollisionPolygon *polygon = *polygonRef;
    PenetrationResult result;
    VecFx32 axis;
    VecFx32 offset;
    VecFx32 dir;
    fx32 center;
    fx32 extent;
    u8 edgeCount;
    u8 i;
    u8 j;

    result = MakePenetrationResult();
    offset = VecSub(&box->center, &polygon->edges[0].vertex);
    if (!TestSignedSeparatingAxis(GetObbProjectedRadius(box, &polygon->normal), &offset, &polygon->normal, 0, &result)) {
        return FALSE;
    }
    edgeCount = polygon->edgeCount;
    for (i = 0; i < 3; i++) {
        extent = GetProjectedInterval(polygon, &box->axes[i], &center);
        extent += box->halfExtents[i];
        center -= VEC_DotProduct(&box->center, &box->axes[i]);
        if (!UpdateSignedPenetrationDepth(extent, center, &box->axes[i], 0, &result)) {
            return FALSE;
        }
        if (VEC_DotProduct(&box->axes[i], &polygon->normal) < 0) {
            NegateVecFx32Into(&dir, &box->axes[i]);
        } else {
            dir = box->axes[i];
        }
        for (j = 0; j < edgeCount; j++) {
            if (!GetCrossIfNonParallel(&dir, &polygon->edges[j].direction, &axis)) {
                NormalizeIfShort(&axis);
                FlipVectorIfDotNegative(&axis, &polygon->edges[j].normal);
                SubtractVecFx32Into(&offset, &box->center, &polygon->edges[j].vertex);
                if (!TestSeparatingAxis(ProjectObbExtentExcludingAxis(box, &axis, i), &offset, &axis, 0, &result)) {
                    return FALSE;
                }
            }
        }
    }
    WritePenetrationContact(&result, contact, flags);
    return TRUE;
}
