#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    s32 length;
    s32 radius;
} CollisionCylinder;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    s32 length;
} CollisionSegment;

typedef struct SegmentShapeRef {
    CollisionSegment *segment;
    u8 pad_04[0x18];
    s32 kind;
} SegmentShapeRef;

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
    s32 minDepth;
    VecFx32 depthAxis;
    s8 depthSign;
    u8 depthFeature;
    u8 pad_2E[2];
    s8 enterSign;
    u8 touching;
    u8 enterFeature;
    u8 pad_33;
} SweepResult;

typedef struct SweepContact {
    s32 depth;
    VecFx32 normal;
    s32 time;
    u8 feature;
} SweepContact;

typedef struct CollisionDisc {
    VecFx32 center;
    s32 radius;
    VecFx32 normal;
} CollisionDisc;

typedef struct EdgeBasis {
    VecFx32 tangent;
    VecFx32 binormal;
    VecFx32 normal;
} EdgeBasis;

typedef struct Vec2Fx32 {
    s32 x;
    s32 y;
} Vec2Fx32;

#define FX_ABS(value) ((value) < 0 ? -(value) : (value))

extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern BOOL ClipRayAgainstPlane_01fff6c8(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern s64 LongDiv_02023ba4(s64 numerator, s64 denominator);
extern s64 DivRem_02023dbc(s32 numerator, s32 denominator);
extern void InitHitQuery_0203ac24(SweepResult *result);
extern void InitSegmentFromEndpoints_0203b1f0(CollisionSegment *segment);
extern BOOL TestSegmentAgainstPolygon_0203c258(SegmentShapeRef *segmentRef, CollisionPolygon **polygonRef, SweepContact *contact, u32 flags);
extern fx32 ScaleDotProductFraction_0203d658(const VecFx32 *a, fx32 scale, const VecFx32 *b);
extern fx32 ComputeDirectionalExtent_0203d718(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern BOOL SweepIntervalOnAxis_0204774c(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact_0204792c(SweepResult *result, SweepContact *contact, u32 flags, const VecFx32 *velocity);
extern void SweepDiscAgainstEdge_0204970c(const VecFx32 *offset, const CollisionDisc *disc, const CollisionEdge *edge, const VecFx32 *binormal, const VecFx32 *normal, const VecFx32 *velocity, fx32 distance, s32 sign, VecFx32 *out);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern BOOL NormalizeUnlessDefault_0204a980(VecFx32 *vec);
extern BOOL NormalizeIfShort_0204a9b4(VecFx32 *vec);
extern BOOL GetCrossIfNonParallel_0204a9e4(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern VecFx32 GetUnitRejectionFromAxis_0204aea8(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 AverageVecs_0204b604(s32 count, ...);
extern void ScaleVecFx32ComponentsConditional_0204b6c4(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern void ScaleVecComponentsConditional_0204b728(VecFx32 *vec, s32 scale, s32 skipHorizontal);
extern void AddScaledDirection_0204b834(VecFx32 *out, fx32 scale, const VecFx32 *up, const VecFx32 *base, BOOL vertical);
extern BOOL IsCrossNearZero_0204b918(const VecFx32 *a, const VecFx32 *b, VecFx32 *out, BOOL vertical);
extern VecFx32 GetNormalizedAxisRejectionMasked_0204bd6c(const VecFx32 *vec, const VecFx32 *axis, BOOL vertical);
extern void BuildBasisMatrix_0204bf28(const VecFx32 *a, const VecFx32 *b, EdgeBasis *out);

static inline void SetDirs(VecFx32 *first, VecFx32 *second, const VecFx32 *v)
{
    VecFx32 unit;
    VEC_NormalizeUnchecked_01ff9f88(v, &unit);
    *first = unit;
    *second = *(VecFx32 *)&unit;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline Vec2Fx32 MakeVec2(fx32 x, fx32 y)
{
    Vec2Fx32 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

static inline fx32 LengthSq(const VecFx32 *vec)
{
    return VEC_DotProduct_01ff9e6c(vec, vec);
}

static inline fx32 AbsFx(fx32 value)
{
    return value < 0 ? -value : value;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

static inline s32 Remainder(s32 numerator, s32 denominator)
{
    return (s32)(DivRem_02023dbc(numerator, denominator) >> 32);
}

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    InitHitQuery_0203ac24(&result);
    return result;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add_01ff9e0c(a, b, &sum);
    return sum;
}

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract_01ff9e3c(a, b, &diff);
    return diff;
}

static inline VecFx32 HalveVec(VecFx32 vec)
{
    vec.x >>= 1;
    vec.y >>= 1;
    vec.z >>= 1;
    return vec;
}

static inline VecFx32 NegateVec(VecFx32 vec)
{
    NegateVecFx32_0204aa40(&vec);
    return vec;
}

static inline VecFx32 ScaleVec(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&vec, scale);
    return vec;
}

static inline VecFx32 ScaleComponents(VecFx32 vec, s32 scale, BOOL vertical)
{
    ScaleVecComponentsConditional_0204b728(&vec, scale, vertical);
    return vec;
}

static inline void SubtractVecConditional(VecFx32 *vec, const VecFx32 *offset, BOOL vertical)
{
    if (!vertical) {
        vec->x -= offset->x;
        vec->z -= offset->z;
    }
    vec->y -= offset->y;
}

static inline VecFx32 RejectAlongEdgeMasked(const VecFx32 *vec, const CollisionEdge *edge, fx32 amount, BOOL vertical)
{
    VecFx32 offset;
    VecFx32 projected;
    VecFx32 rejection;
    VecFx32 *offsetPtr;

    projected = edge->direction;
    ScaleVecFx32ComponentsConditional_0204b6c4(&projected, amount, vertical);
    offsetPtr = &offset;
    *offsetPtr = projected;
    rejection = *vec;
    SubtractVecConditional(&rejection, offsetPtr, vertical);
    return rejection;
}

static inline VecFx32 RejectAlongEdge(const VecFx32 *vec, const CollisionEdge *edge, fx32 amount)
{
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;
    scaledAxis = edge->direction;
    ScaleVecFx32InPlace_0204a5e4(&scaledAxis, amount);
    projection = scaledAxis;
    VEC_Subtract_01ff9e3c(vec, &projection, &rejection);
    return rejection;
}

static inline VecFx32 RejectAlongAxis(const VecFx32 *vec, const VecFx32 *axis, fx32 amount)
{
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;
    scaledAxis = *axis;
    ScaleVecFx32InPlace_0204a5e4(&scaledAxis, amount);
    projection = scaledAxis;
    VEC_Subtract_01ff9e3c(vec, &projection, &rejection);
    return rejection;
}

static inline VecFx32 RejectAlongValue(const VecFx32 *vec, VecFx32 axis, fx32 amount)
{
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;
    scaledAxis = axis;
    ScaleVecFx32InPlace_0204a5e4(&scaledAxis, amount);
    projection = scaledAxis;
    VEC_Subtract_01ff9e3c(vec, &projection, &rejection);
    return rejection;
}

static inline VecFx32 Normalized(const VecFx32 *vec)
{
    VecFx32 unit;
    VEC_NormalizeUnchecked_01ff9f88(vec, &unit);
    return unit;
}

static inline VecFx32 CrossVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    VEC_CrossProduct_01ff9ea8(a, b, &cross);
    return cross;
}

static inline VecFx32 MultAddVec(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 sum;
    VEC_MultAdd_01ffa09c(scale, v, add, &sum);
    return sum;
}

static inline VecFx32 CrossConditional(const VecFx32 *a, const VecFx32 *b, BOOL vertical)
{
    VecFx32 cross;
    if (!vertical) {
        VEC_CrossProduct_01ff9ea8(a, b, &cross);
    } else {
        cross.x = -(fx32)(((fx64)a->z * b->y + 0x800) >> 12);
        cross.y = 0;
        cross.z = (fx32)(((fx64)a->x * b->y + 0x800) >> 12);
    }
    return cross;
}

typedef struct BasisCopy {
    fx32 m[9];
} BasisCopy;

static inline EdgeBasis BuildEdgeBasis(const VecFx32 *a, const VecFx32 *b)
{
    EdgeBasis out;
    EdgeBasis built;
    BuildBasisMatrix_0204bf28(a, b, &built);
    *(BasisCopy *)&out = *(BasisCopy *)&built;
    return out;
}

static inline void SweepDisc(VecFx32 offset, const CollisionDisc *disc, const CollisionEdge *edge, EdgeBasis *basis, const VecFx32 *velocity, VecFx32 *out)
{
    SweepDiscAgainstEdge_0204970c(&offset, disc, edge, &basis->binormal, &basis->normal, velocity, VEC_DotProduct_01ff9e6c(&basis->binormal, &offset), -1, out);
}

BOOL SweepCylinderAgainstPolygon_020456c0(CylinderShapeRef *cylinderRef, CollisionPolygon **polygonRef, SweepContact *contact, u32 flags, const VecFx32 *velocity)
{
    BOOL isCapsule = 3 == cylinderRef->kind;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    CollisionPolygon *polygon = *polygonRef;
    u8 i;
    int polygonVertical;
    s32 dirTangent;
    SegmentShapeRef segmentRef;
    CollisionSegment segment;
    VecFx32 center;
    VecFx32 halfSegment;
    VecFx32 axis;
    SweepResult result;
    VecFx32 normal;
    VecFx32 edgeAxis;
    VecFx32 offset;
    VecFx32 dir;
    VecFx32 facing;
    VecFx32 cross;
    VecFx32 crossUnit;
    VecFx32 radial;
    VecFx32 projected;
    VecFx32 radialScaled;
    VecFx32 tangent;
    VecFx32 startOffset;
    VecFx32 endOffset;
    VecFx32 rejection[2];
    VecFx32 flat[2];
    VecFx32 perp;
    VecFx32 binormal;
    EdgeBasis basis;
    VecFx32 discOffset;
    const CollisionEdge *edge;
    CollisionDisc disc;
    VecFx32 vertexNormal;
    VecFx32 vertexTangent;
    VecFx32 endpointOffset[2];
    VecFx32 endpointRejection[2];
    VecFx32 toPrev;
    Vec2Fx32 local;
    s32 extent;
    s32 isPerpendicular;
    Vec2Fx32 edgeLocal;
    Vec2Fx32 dirLocal;
    int vertical;
    fx32 endpointDist[2];
    const VecFx32 *crossRef;
    u8 extreme[2];
    const VecFx32 *radialRef;
    const VecFx32 *perpRef;
    BOOL bothVertical;
    VecFx32 perpValue;
    u32 isParallel;
    VecFx32 toNext;
    int radiusSq;
    int halfLength;
    s32 approach;
    s32 alignment;
    u8 edgeCount;
    VecFx32 average;
    VecFx32 dirCopy[1];

    vertical = cylinder->direction.x == 0 && cylinder->direction.z == 0;
    polygonVertical = polygon->normal.x == 0 && polygon->normal.z == 0;
    approach = VEC_DotProduct_01ff9e6c(velocity, &polygon->normal);
    if (approach < 0 && isCapsule) {
        {
            fx32 facingDot = VEC_DotProduct_01ff9e6c(&polygon->normal, &cylinder->direction);
            segment.start = 0 < facingDot ? cylinder->start : cylinder->end;
        }
        AddScaledDirection_0204b834(&segment.start, -cylinder->radius, &polygon->normal, &segment.start, polygonVertical);
        segment.end = AddVec(&segment.start, velocity);
        InitSegmentFromEndpoints_0203b1f0(&segment);
        segmentRef.segment = &segment;
        if (TestSegmentAgainstPolygon_0203c258(&segmentRef, polygonRef, contact, flags)) {
            return TRUE;
        }
    }

    bothVertical = vertical && polygonVertical;
    center = vertical ? MakeVec(cylinder->start.x, (cylinder->start.y + cylinder->end.y) / 2, cylinder->start.z)
                      : (average = AverageVecs_0204b604(2, &cylinder->start, &cylinder->end));
    halfSegment = vertical ? MakeVec(0, FX_ABS(cylinder->end.y - cylinder->start.y) / 2, 0) : HalveVec(SubtractVec(&cylinder->end, &cylinder->start));
    halfLength = cylinder->length / 2;
    axis = cylinder->direction;
    result = MakeSweepResult();
    if (bothVertical) {
        alignment = 0x1000;
    } else {
        alignment = VEC_DotProduct_01ff9e6c(&polygon->normal, &axis);
        if (alignment < 0) {
            alignment = -alignment;
        }
    }
    isParallel = 0x1000 == alignment;
    isPerpendicular = TRUE;
    if (alignment != 0) {
        isPerpendicular = FALSE;
    }
    offset = SubtractVec(&center, &polygon->edges[0].vertex);

    if (isCapsule) {
        extent = isParallel ? halfLength + cylinder->radius : isPerpendicular ? cylinder->radius : cylinder->radius + AbsFx(VEC_DotProduct_01ff9e6c(&polygon->normal, &halfSegment));
    } else if (isParallel) {
        extent = halfLength;
    } else if (isPerpendicular) {
        extent = cylinder->radius;
    } else {
        extent = ComputeDirectionalExtent_0203d718(cylinderRef->cylinder, &axis, halfLength * 2, &polygon->normal);
    }
    if (!SweepIntervalOnAxis_0204774c(extent, VEC_DotProduct_01ff9e6c(&polygon->normal, &offset), &polygon->normal, 0, velocity, &result, NULL)) {
        return FALSE;
    }

    if (0 == approach && isCapsule && result.minDepth == 0) {
        if (contact != NULL) {
            contact->time = -1;
            contact->depth = 0;
            contact->normal = result.depthAxis;
            contact->feature = result.depthFeature;
            if (-1 == result.depthSign) {
                NegateVecFx32_0204aa40(&contact->normal);
            }
        }
        return TRUE;
    }

    edgeCount = polygon->edgeCount;
    SetDirs(dirCopy, &dir, velocity);
    radiusSq = (fx32)(((fx64)cylinder->radius * cylinder->radius + 0x800) >> 12);
    if ((bothVertical && (cylinder->direction.y >= 0) != (polygon->normal.y >= 0)) || VEC_DotProduct_01ff9e6c(&polygon->normal, &axis) < 0) {
        facing = ScaleComponents(axis, -1, vertical);
    } else {
        facing = axis;
    }

    for (i = 0; i < edgeCount; i++) {
        s16 feature = 0;

        if (i % 2 == 0) {
            int next = 1 + i;
            if (next == edgeCount) {
                next = i;
            }
            offset = SubtractVec(&center, &polygon->edges[next].vertex);
        }
        extent = cylinder->radius;
        if (bothVertical) {
            edgeAxis = ((CollisionEdge *)polygon + i)->normal;
        } else if (IsCrossNearZero_0204b918(&polygon->edges[i].direction, &facing, &edgeAxis, vertical)) {
            if (GetCrossIfNonParallel_0204a9e4(&polygon->edges[i].direction, &dir, &cross)) {
                edgeAxis = RejectAlongEdgeMasked(&offset, (CollisionEdge *)polygon + i, VEC_DotProduct_01ff9e6c(&offset, &polygon->edges[i].direction), vertical);
                if (NormalizeUnlessDefault_0204a980(&edgeAxis)) {
                    continue;
                }
            } else {
                s32 side;
                s32 remaining;
                crossRef = &Normalized(&cross);
                crossUnit = *crossRef;
                radialRef = &GetNormalizedAxisRejectionMasked_0204bd6c(&dir, &polygon->edges[i].direction, vertical);
                radial = *radialRef;
                side = Sign(VEC_DotProduct_01ff9e6c(&radial, &offset));
                projected = ScaleVec(*crossRef, VEC_DotProduct_01ff9e6c(&offset, &crossUnit));
                remaining = radiusSq - VEC_DotProduct_01ff9e6c(&projected, &projected);
                if (0 > remaining) {
                    remaining = 0;
                }
                radialScaled = ScaleVec(radial, side * FX_Sqrt_01ff9cfc(remaining));
                VEC_Add_01ff9e0c(&projected, &radialScaled, &edgeAxis);
                if (0 == edgeAxis.x && edgeAxis.y == 0 && edgeAxis.z == 0) {
                    continue;
                }
                VEC_NormalizeUnchecked_01ff9f88(&edgeAxis, &edgeAxis);
            }
            if (VEC_DotProduct_01ff9e6c(&edgeAxis, &polygon->edges[i].normal) <= 0) {
                continue;
            }
            feature = 1;
        } else {
            VEC_NormalizeUnchecked_01ff9f88(&edgeAxis, &edgeAxis);
        }
        if (!ClipRayAgainstPlane_01fff6c8(extent, VEC_DotProduct_01ff9e6c(&edgeAxis, &offset), &edgeAxis, feature, velocity, &result, NULL)) {
            return FALSE;
        }

        if (!isParallel || isCapsule) {
            s32 along;
            tangent = CrossConditional(&edgeAxis, &facing, vertical);
            local = MakeVec2(vertical ? (facing.y > 0 ? offset.y : -offset.y) : VEC_DotProduct_01ff9e6c(&offset, &facing), VEC_DotProduct_01ff9e6c(&offset, &tangent));
            edgeLocal = MakeVec2(isParallel ? 0 : VEC_DotProduct_01ff9e6c(&polygon->edges[i].direction, &facing),
                                 isParallel ? 0x1000 : VEC_DotProduct_01ff9e6c(&polygon->edges[i].direction, &tangent));
            along = local.x - (isParallel ? 0 : (fx32)LongDiv_02023ba4((s64)local.y * edgeLocal.x, edgeLocal.y));
            if (0 > along) {
                along = -along;
            }
            if (along > halfLength) {
                u8 nearest;
                startOffset = SubtractVec(&cylinder->start, &polygon->edges[i].vertex);
                endOffset = SubtractVec(&cylinder->end, &polygon->edges[i].vertex);
                perpRef = &GetUnitRejectionFromAxis_0204aea8(&dir, &polygon->edges[i].direction);
                perp = *perpRef;
                rejection[0] = RejectAlongEdge(&startOffset, (CollisionEdge *)polygon + i, VEC_DotProduct_01ff9e6c(&startOffset, &polygon->edges[i].direction));
                rejection[1] = RejectAlongEdge(&endOffset, (CollisionEdge *)polygon + i, VEC_DotProduct_01ff9e6c(&endOffset, &polygon->edges[i].direction));
                flat[0] = RejectAlongValue(&rejection[0], perpValue = perp, VEC_DotProduct_01ff9e6c(&rejection[0], &perp));
                flat[1] = RejectAlongValue(&rejection[1], perpValue, VEC_DotProduct_01ff9e6c(&rejection[1], &perp));
                if (isCapsule) {
                    fx32 flatDist0 = LengthSq(&flat[0]);
                    s32 edgeRadius;
                    fx32 flatDist1 = LengthSq(&flat[1]);
                    s32 len;
                    s32 axial;
                    if (flatDist0 - flatDist1 < 16 && flatDist0 - flatDist1 > -16) {
                        nearest = VEC_DotProduct_01ff9e6c(&rejection[0], &rejection[0]) >= VEC_DotProduct_01ff9e6c(&rejection[1], &rejection[1]);
                    } else {
                        fx32 len0 = flatDist0 < radiusSq ? FX_Sqrt_01ff9cfc(radiusSq - flatDist0) : 0;
                        fx32 len1 = flatDist1 < radiusSq ? FX_Sqrt_01ff9cfc(radiusSq - flatDist1) : 0;
                        fx32 gap0 = -len0 + AbsDotProduct_0204a96c(&rejection[0], &perp);
                        nearest = gap0 >= -len1 + AbsDotProduct_0204a96c(&rejection[1], &perp);
                    }
                    len = VEC_DotProduct_01ff9e6c(&flat[nearest], &flat[nearest]);
                    len = len < radiusSq ? FX_Sqrt_01ff9cfc(radiusSq - len) : 0;
                    normal = flat[nearest];
                    if (0 != len) {
                        fx32 slide = VEC_DotProduct_01ff9e6c(&perp, &rejection[nearest]);
                        if (FX_ABS(slide) <= len) {
                            normal = rejection[nearest];
                        } else {
                            normal = MultAddVec(len * (slide >= 0 ? 1 : -1), &perp, &normal);
                        }
                    }
                    if ((normal.x != 0 || normal.y != 0 || normal.z != 0) && VEC_DotProduct_01ff9e6c(&normal, &polygon->edges[i].normal) >= 0) {
                        axial = VEC_DotProduct_01ff9e6c(&normal, &axis);
                        if (axial * (!nearest ? -1 : 1) > 0) {
                            nearest ^= 1;
                        }
                        NormalizeIfShort_0204a9b4(&normal);
                        edgeRadius = cylinder->radius;
                        if (!ClipRayAgainstPlane_01fff6c8(edgeRadius, VEC_DotProduct_01ff9e6c(&normal, &rejection[nearest]), &normal, 1, velocity, &result, NULL)) {
                            return FALSE;
                        }
                    }
                } else if (!isParallel && VEC_DotProduct_01ff9e6c(&axis, &polygon->edges[i].direction) != 0 && AbsDotProduct_0204a96c(&polygon->edges[i].direction, &dir) < 0xff0) {
                    s32 side0;
                    s32 side1;
                    binormal = CrossVec(&edgeAxis, &polygon->edges[i].direction);
                    side0 = VEC_DotProduct_01ff9e6c(&rejection[0], &binormal);
                    side1 = VEC_DotProduct_01ff9e6c(&rejection[1], &binormal);
                    if (side0 != side1) {
                        if (side1 < 0) {
                            side1 = -side1;
                        }
                        side0 = FX_ABS(side0);
                        nearest = side0 >= side1;
                        basis = BuildEdgeBasis(&polygon->edges[i].direction, &dir);
                        disc.center = !nearest ? cylinder->start : cylinder->end;
                        disc.radius = cylinder->radius;
                        disc.normal = axis;
                        discOffset = SubtractVec(&disc.center, &polygon->edges[i].vertex);
                        if (VEC_DotProduct_01ff9e6c(&discOffset, &basis.binormal) < 0) {
                            NegateVecFx32_0204aa40(&basis.binormal);
                        }
                        edge = (CollisionEdge *)polygon + i;
                        SweepDisc(SubtractVec(&disc.center, &edge->vertex), &disc, edge, &basis, velocity, &normal);
                        if (VEC_DotProduct_01ff9e6c(&normal, &edge->normal) < 0) {
                            NegateVecFx32_0204aa40(&normal);
                        }
                        if (!ClipRayAgainstPlane_01fff6c8(ScaleDotProductFraction_0203d658(&disc.normal, disc.radius, &normal), VEC_DotProduct_01ff9e6c(&normal, &rejection[nearest]), &normal, 1, velocity, &result, NULL)) {
                            return FALSE;
                        }
                    }
                }
            }
        }
    }

    if (!isCapsule && !isParallel) {
        fx32 minProjection = 0x7FFFFFFF;
        fx32 maxProjection = 0x80000000;
        u8 j;
        for (j = 0; j < (u32)edgeCount; j++) {
            fx32 projection = VEC_DotProduct_01ff9e6c(&polygon->edges[j].vertex, &axis);
            if (minProjection > projection) {
                minProjection = projection;
                extreme[0] = j;
            }
            if (maxProjection < projection) {
                extreme[1] = j;
                maxProjection = projection;
            }
        }
        for (j = 0; j < 2; j++) {
            normal = j == 0 ? NegateVec(axis) : axis;
            offset = SubtractVec(&center, &polygon->edges[extreme[j]].vertex);
            if (!ClipRayAgainstPlane_01fff6c8(halfLength, VEC_DotProduct_01ff9e6c(&normal, &offset), &normal, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
    }

    {
        u8 prev = edgeCount - 1;
        u8 k;
        for (k = 0; k < edgeCount; k += 1, prev = Remainder(prev + 1, edgeCount)) {
            s32 len;
            s32 axial;
            s32 radialDist;
            s32 along;
            s32 shift;
            s32 nextDot;
            s32 prevDot;
            s32 vertexRadius;
            offset = SubtractVec(&center, &polygon->edges[k].vertex);
            if (IsCrossNearZero_0204b918(&dir, &axis, &vertexNormal, vertical)) {
                vertexNormal = GetNormalizedAxisRejectionMasked_0204bd6c(&offset, &axis, vertical);
            } else {
                NormalizeIfShort_0204a9b4(&vertexNormal);
            }
            radialDist = VEC_DotProduct_01ff9e6c(&offset, &vertexNormal);
            len = FX_ABS(radialDist) < cylinder->radius ? FX_Sqrt_01ff9cfc(radiusSq - (fx32)(((fx64)radialDist * radialDist + 0x800) >> 12)) : 0;
            vertexTangent = CrossConditional(&vertexNormal, &axis, vertical);
            dirTangent = VEC_DotProduct_01ff9e6c(&dir, &vertexTangent);
            dirLocal = MakeVec2(VEC_DotProduct_01ff9e6c(&dir, &axis), dirTangent);
            axial = VEC_DotProduct_01ff9e6c(&offset, &axis);
            shift = VEC_DotProduct_01ff9e6c(&offset, &vertexTangent);
            shift = dirTangent == 0 ? 0 : (fx32)LongDiv_02023ba4((s64)dirLocal.x * (shift - len), dirTangent);
            along = axial - shift;
            if (along >= -halfLength && along <= halfLength) {
                normal = GetNormalizedAxisRejectionMasked_0204bd6c(&offset, &axis, vertical);
            } else {
                u8 nearest;
                if (!isCapsule) {
                    continue;
                }
                if (dirTangent) {
                    s32 len1;
                    s32 gap0;
                    s32 len0;
                    endpointOffset[0] = SubtractVec(&cylinder->start, &polygon->edges[k].vertex);
                    endpointOffset[1] = SubtractVec(&cylinder->end, &polygon->edges[k].vertex);
                    endpointRejection[0] = RejectAlongAxis(&endpointOffset[0], dirCopy, VEC_DotProduct_01ff9e6c(&endpointOffset[0], &dir));
                    endpointRejection[1] = RejectAlongAxis(&endpointOffset[1], dirCopy, VEC_DotProduct_01ff9e6c(&endpointOffset[1], &dir));
                    endpointDist[0] = VEC_DotProduct_01ff9e6c(&endpointRejection[0], &endpointRejection[0]);
                    endpointDist[1] = VEC_DotProduct_01ff9e6c(&endpointRejection[1], &endpointRejection[1]);
                    len0 = endpointDist[0] < radiusSq ? FX_Sqrt_01ff9cfc(radiusSq - endpointDist[0]) : 0;
                    len1 = endpointDist[1] < radiusSq ? FX_Sqrt_01ff9cfc(radiusSq - endpointDist[1]) : 0;
                    gap0 = -len0 + AbsDotProduct_0204a96c(&endpointOffset[0], &dir);
                    nearest = gap0 >= -len1 + AbsDotProduct_0204a96c(&endpointOffset[1], &dir);
                } else {
                    nearest = 0 > along;
                    endpointOffset[nearest] = SubtractVec(!nearest ? &cylinder->start : &cylinder->end, &polygon->edges[k].vertex);
                    endpointRejection[nearest] = RejectAlongAxis(&endpointOffset[nearest], dirCopy, VEC_DotProduct_01ff9e6c(&endpointOffset[nearest], &dir));
                    endpointDist[nearest] = VEC_DotProduct_01ff9e6c(&endpointRejection[nearest], &endpointRejection[nearest]);
                }
                len = endpointDist[nearest] < radiusSq ? FX_Sqrt_01ff9cfc(radiusSq - endpointDist[nearest]) : 0;
                normal = endpointRejection[nearest];
                normal = MultAddVec(len * Sign(VEC_DotProduct_01ff9e6c(&dir, &endpointOffset[nearest])), &dir, &normal);
                VEC_NormalizeUnchecked_01ff9f88(&normal, &normal);
                offset = endpointOffset[nearest];
            }
            toPrev = SubtractVec(&polygon->edges[prev].vertex, &polygon->edges[k].vertex);
            toNext = SubtractVec(&polygon->edges[Remainder(k + 1, edgeCount)].vertex, &polygon->edges[k].vertex);
            prevDot = VEC_DotProduct_01ff9e6c(&toPrev, &normal);
            nextDot = VEC_DotProduct_01ff9e6c(&toNext, &normal);
            if (prevDot <= 0 && nextDot <= 0) {
                vertexRadius = cylinder->radius;
                if (!ClipRayAgainstPlane_01fff6c8(vertexRadius, VEC_DotProduct_01ff9e6c(&normal, &offset), &normal, 1, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
    }

    return ResolveSweepContact_0204792c(&result, contact, flags, velocity);
}
