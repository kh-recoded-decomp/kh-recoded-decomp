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

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 GetObbProjectedRadius_0203d4d0(const OrientedBox *box, const VecFx32 *axis);
extern fx32 ProjectObbExtentExcludingAxis_0203d568(OrientedBox *box, const VecFx32 *direction, int excludedAxis);
extern fx32 GetProjectedInterval_0203d774(CollisionPolygon *shape, const VecFx32 *axis, fx32 *center);
extern void func_02047cec(SweepResult *out);
extern void SubtractVecFx32Out_02047d2c(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL func_02047d5c(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern void NegateVecFx32Out_02047fc8(VecFx32 *out, const VecFx32 *v);
extern BOOL SweepIntervalOnAxis_0204774c(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern BOOL SweepAlongProjectedAxis_020481c4(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL func_0204a9e4(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FlipVectorIfDotNegative_0204abd0(VecFx32 *a, const VecFx32 *b);

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    func_02047cec(&result);
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    SubtractVecFx32Out_02047d2c(&diff, a, b);
    return diff;
}

BOOL SweepObbAgainstPolygon_02048020(OrientedBox **boxRef, CollisionPolygon **polygonRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    OrientedBox *box = *boxRef;
    CollisionPolygon *polygon = *polygonRef;
    SweepResult result;
    VecFx32 axis;
    VecFx32 offset;
    VecFx32 dir;
    fx32 center;
    fx32 extent;
    u8 edgeCount;
    u8 i;
    u8 j;

    result = MakeSweepResult();
    offset = VecSub(&box->center, &polygon->edges[0].vertex);
    extent = GetObbProjectedRadius_0203d4d0(box, &polygon->normal);
    axis = polygon->normal;
    if (!func_02047d5c(extent, &offset, &axis, 0, velocity, &result, NULL)) {
        return FALSE;
    }
    edgeCount = polygon->edgeCount;
    for (i = 0; i < 3; i++) {
        extent = GetProjectedInterval_0203d774(polygon, &box->axes[i], &center);
        extent += box->halfExtents[i];
        center = VEC_DotProduct_01ff9e6c(&box->center, &box->axes[i]) - center;
        axis = box->axes[i];
        if (!SweepIntervalOnAxis_0204774c(extent, center, &axis, 0, velocity, &result, NULL)) {
            return FALSE;
        }
        if (VEC_DotProduct_01ff9e6c(&box->axes[i], &polygon->normal) < 0) {
            NegateVecFx32Out_02047fc8(&dir, &box->axes[i]);
        } else {
            dir = box->axes[i];
        }
        for (j = 0; j < edgeCount; j++) {
            if (!func_0204a9e4(&dir, &polygon->edges[j].direction, &axis)) {
                VEC_NormalizeUnchecked_01ff9f88(&axis, &axis);
                FlipVectorIfDotNegative_0204abd0(&axis, &polygon->edges[j].normal);
                SubtractVecFx32Out_02047d2c(&offset, &box->center, &polygon->edges[j].vertex);
                if (!SweepAlongProjectedAxis_020481c4(ProjectObbExtentExcludingAxis_0203d568(box, &axis, i), &offset, &axis, 0, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
    }
    return ResolveSweepContact_0204792c(&result, contact, flags, velocity);
}
