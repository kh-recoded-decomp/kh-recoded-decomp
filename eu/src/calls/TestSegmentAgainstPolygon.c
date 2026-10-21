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

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern s64 FX_DivFx64c(fx32 numerator, fx32 denominator);
extern s64 _ll_sdiv(s64 numerator, s64 denominator);
extern BOOL UpdateSignedPenetrationDepth(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId,
                                         PenetrationResult *result);
extern BOOL UpdatePenetrationDepth(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId,
                                   PenetrationResult *result);
extern void WritePenetrationContact(const PenetrationResult *result, void *contact, u32 flags);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void ProjectPositionAtTime(s64 time, const VecFx32 *velocity, const VecFx32 *origin, VecFx32 *out);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL GetCrossIfNonParallel(const VecFx32 *a, const VecFx32 *b, VecFx32 *cross);
extern fx32 FlipVectorIfDotNegative(VecFx32 *a, const VecFx32 *b);
extern void NegateVecFx32(VecFx32 *vec);
extern VecFx32 AverageVecs(s32 count, ...);

static inline PenetrationResult MakeEmptyResult(void)
{
    PenetrationResult result;
    result.depth = 0x7FFFFFFF;
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract(a, b, &diff);
    return diff;
}

static inline VecFx32 ScaleVec(const VecFx32 *vec, fx32 scale)
{
    VecFx32 scaled = *vec;
    ScaleVecFx32InPlace(&scaled, scale);
    return scaled;
}

static inline VecFx32 FacingAlong(const VecFx32 *vec, const VecFx32 *normal)
{
    VecFx32 facing = *vec;
    FlipVectorIfDotNegative(&facing, normal);
    return facing;
}

static inline VecFx32 PositionAtTime(s64 time, const VecFx32 *velocity, const VecFx32 *origin)
{
    VecFx32 position;
    ProjectPositionAtTime(time, velocity, origin, &position);
    return position;
}

static inline VecFx32 FacingNormal(const VecFx32 *normal, fx32 approach)
{
    VecFx32 facing = *normal;
    if (approach < 0) {
        NegateVecFx32(&facing);
    }
    return facing;
}

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

#define FX_ABS(value) ((value) < 0 ? -(value) : (value))

/* Segment against polygon. With flags & 2 it is a separating-axis overlap test (the polygon normal,
 * then each edge crossed with the segment direction) that writes the shallowest penetration;
 * otherwise the segment must cross the polygon's plane at a point inside the edges, and the hit
 * gets the crossing as a fraction of the segment length. */
BOOL TestSegmentAgainstPolygon(const CollisionShape *segmentShape, const CollisionShape *polygonShape,
                               CollisionHit *hit, u32 flags)
{
    CollisionSegment *segment = segmentShape->data;
    CollisionPolygon *polygon = polygonShape->data;
    VecFx32 direction = segment->direction;
    fx32 length = segment->length;

    if (length == 0) {
        return FALSE;
    }
    if (flags & 2) {
        VecFx32 center = AverageVecs(2, &segment->start, &segment->end);
        VecFx32 halfAxis = ScaleVec(&direction, length / 2);
        PenetrationResult result = MakeEmptyResult();
        VecFx32 edgeNormal;
        VecFx32 offset = VecSub(&center, &polygon->edges[0].vertex);
        VecFx32 facing;
        fx32 extent;
        u8 i;
        u8 edgeCount;

        extent = AbsDotProduct(&halfAxis, &polygon->normal);
        if (!UpdateSignedPenetrationDepth(extent, VEC_DotProduct(&polygon->normal, &offset), &polygon->normal, 0,
                                          &result)) {
            return FALSE;
        }
        facing = FacingAlong(&direction, &polygon->normal);
        edgeCount = polygon->edgeCount;
        for (i = 0; i < edgeCount; i++) {
            CollisionEdge *edge = &polygon->edges[i];

            if (!GetCrossIfNonParallel(&edge->direction, &facing, &edgeNormal)) {
                VEC_Normalize(&edgeNormal, &edgeNormal);
                offset = VecSub(&center, &edge->vertex);
                if (!UpdatePenetrationDepth(0, VEC_DotProduct(&edgeNormal, &offset), &edgeNormal, 0, &result)) {
                    return FALSE;
                }
            }
        }
        WritePenetrationContact(&result, hit, flags);
        return TRUE;
    } else {
        VecFx32 offset = VecSub(&segment->start, &polygon->edges[0].vertex);
        fx32 distance = VEC_DotProduct(&offset, &polygon->normal);
        fx32 speed = VEC_DotProduct(&direction, &polygon->normal);
        BOOL separated;
        fx32 reach;
        s64 time;
        VecFx32 point;
        VecFx32 edgeOffset;
        u8 edgeCount;
        u8 i;

        if (speed > 0x10) {
            separated = distance > 0x10 || distance == 0;
        } else if (speed < -0x10) {
            separated = distance < -0x10;
        } else {
            return FALSE;
        }
        if (separated) {
            return FALSE;
        }
        reach = FxMul(speed, length);
        if (FX_ABS(reach) < FX_ABS(distance)) {
            return FALSE;
        }
        time = FX_DivFx64c(distance, -speed);
        point = PositionAtTime(time, &direction, &segment->start);
        edgeCount = polygon->edgeCount;
        for (i = 0; i < edgeCount; i++) {
            if (i % 2 == 0) {
                int next = i + 1;

                if (next == edgeCount) {
                    next = i;
                }
                edgeOffset = VecSub(&point, &polygon->edges[next].vertex);
            }
            if (VEC_DotProduct(&edgeOffset, &polygon->edges[i].normal) > 0x10) {
                return FALSE;
            }
        }
        if (hit != NULL) {
            hit->time = (fx32)(_ll_sdiv(time << 12, length) >> 5);
            /* The cast keeps this negation apart from the one in the division above (the ROM
             * negates speed twice). */
            hit->normal = FacingNormal(&polygon->normal, -(fx32)speed);
            hit->depth = FX_ABS(reach + distance);
            hit->kind = 0;
            if (flags & 1) {
                NegateVecFx32(&hit->normal);
            }
        }
        return TRUE;
    }
}
