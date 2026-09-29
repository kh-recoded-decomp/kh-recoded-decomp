#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

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

extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern BOOL TestSegmentAgainstPolygon_0203c258(CollisionShape *segmentShape, CollisionShape *polygonShape, void *contact, u32 flags);
extern void func_02047cec(SweepResult *out);
extern void SubtractVecFx32Out_02047d2c(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL func_02047d5c(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern void AddVecFx32Out_02047f98(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern BOOL func_020481c4(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL func_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern void func_02048b30(VecFx32 *out, const VecFx32 *vec, fx32 scale);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_0204a9e4(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FlipVectorIfDotNegative_0204abd0(VecFx32 *a, const VecFx32 *b);
extern void func_0204b604(VecFx32 *out, int count, ...);

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    AddVecFx32Out_02047f98(&sum, a, b);
    return sum;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    SubtractVecFx32Out_02047d2c(&diff, a, b);
    return diff;
}

static inline VecFx32 AverageOfTwo(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 average;
    func_0204b604(&average, 2, a, b);
    return average;
}

static inline VecFx32 ScaleVec(const VecFx32 *vec, fx32 scale)
{
    VecFx32 scaled;
    func_02048b30(&scaled, vec, scale);
    return scaled;
}

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    func_02047cec(&result);
    return result;
}

BOOL SweepSegmentAgainstPolygon_02048c7c(CollisionShape *segmentShape, CollisionShape *polygonShape, void *contact, u32 flags, const VecFx32 *velocity)
{
    CollisionSegment *segment = segmentShape->data;
    CollisionPolygon *polygon = polygonShape->data;
    CollisionShape movedShape;
    CollisionSegment moved;
    VecFx32 direction;
    VecFx32 center;
    VecFx32 halfAxis;
    SweepResult result;
    VecFx32 axis;
    VecFx32 edgeNormal;
    VecFx32 offset;
    VecFx32 facing;
    fx32 length;
    fx32 extent;
    u8 edgeCount;
    u8 i;

    if (!(flags & 4)) {
        moved = *segment;
        moved.end = VecAdd(&moved.end, velocity);
        movedShape.data = &moved;
        return TestSegmentAgainstPolygon_0203c258(&movedShape, polygonShape, contact, flags & 1);
    }

    direction = segment->direction;
    length = segment->length;
    if (length == 0) {
        return FALSE;
    }
    center = AverageOfTwo(&segment->start, &segment->end);
    halfAxis = ScaleVec(&direction, length / 2);
    result = MakeSweepResult();
    offset = VecSub(&center, &polygon->edges[0].vertex);
    extent = AbsDotProduct_0204a96c(&halfAxis, &polygon->normal);
    axis = polygon->normal;
    if (!func_02047d5c(extent, &offset, &axis, 0, velocity, &result, NULL)) {
        return FALSE;
    }
    edgeCount = polygon->edgeCount;
    facing = direction;
    FlipVectorIfDotNegative_0204abd0(&facing, &polygon->normal);
    for (i = 0; i < edgeCount; i++) {
        if (!func_0204a9e4(&polygon->edges[i].direction, &facing, &edgeNormal)) {
            func_01ff9f88(&edgeNormal, &axis);
            SubtractVecFx32Out_02047d2c(&offset, &center, &polygon->edges[i].vertex);
            if (!func_020481c4(0, &offset, &axis, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
    }
    return func_0204792c(&result, contact, flags, velocity);
}
