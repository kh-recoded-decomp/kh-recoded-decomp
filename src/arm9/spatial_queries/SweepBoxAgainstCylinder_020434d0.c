#pragma opt_loop_invariants off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} CollisionBox;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

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

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void InitSweepResult_0203ac24(SweepResult *result);
extern fx32 ProjectBoxExtent_0203d4d0(const CollisionBox *box, const VecFx32 *axis);
extern fx32 ProjectBoxExtentSkipAxis_0203d568(const CollisionBox *box, const VecFx32 *axis, u8 axisIndex);
extern fx32 ComputeDirectionalExtent_0203d718(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern void ComputeWeightedBasisSum_0203ed10(const CollisionBox *box, fx32 weightX, fx32 weightY, fx32 weightZ, VecFx32 *out);
extern void func_0203ed8c(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out);
extern void func_0203ee18(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out);
extern BOOL SweepIntervalOnAxis_0204774c(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern void func_0204a2e0(const Vec2Fx32 *a, const Vec2Fx32 *b, Vec2Fx32 *out);
extern void ScalePairInPlace_0204a350(Vec2Fx32 *pair, fx32 scale);
extern fx32 func_0204a390(const Vec2Fx32 *a, const Vec2Fx32 *b);
extern BOOL NormalizeVec2Fx_0204a460(Vec2Fx32 *vec, Vec2Fx32 *out);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void func_0204a6ac(VecFx32 *vec, fx32 divisor);
extern void func_0204a7bc(s64 time, const VecFx32 *direction, const VecFx32 *origin, VecFx32 *out);
extern BOOL func_0204a9b4(VecFx32 *vec);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern fx32 BlendVectorsBySqrtComplement_0204b59c(VecFx32 *a, const VecFx32 *b, fx32 t, s32 factor, VecFx32 *out);
extern VecFx32 func_0204b604(s32 count, ...);
extern void ScaleVecFx32ComponentsConditional_0204b6c4(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern void NegateVecComponentsConditional_0204b758(VecFx32 *vec, s32 sign, s32 skipHorizontal);
extern VecFx32 func_0204b834(fx32 scale, const VecFx32 *axis, const VecFx32 *base, BOOL vertical);
extern BOOL func_0204b918(const VecFx32 *a, const VecFx32 *b, VecFx32 *out, BOOL vertical);
extern void func_0204b9c8(VecFx32 *out, const VecFx32 *a, const VecFx32 *b, BOOL vertical);

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    InitSweepResult_0203ac24(&result);
    return result;
}

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract_01ff9e3c(a, b, &diff);
    return diff;
}

static inline VecFx32 SubtractVecValue(const VecFx32 *a, VecFx32 b)
{
    VecFx32 diff;
    VEC_Subtract_01ff9e3c(a, &b, &diff);
    return diff;
}

static inline VecFx32 HalveVec(VecFx32 vec)
{
    vec.x >>= 1;
    vec.y >>= 1;
    vec.z >>= 1;
    return vec;
}

static inline VecFx32 Normalized(const VecFx32 *vec)
{
    VecFx32 unit;
    VEC_Normalize_01ff9f88(vec, &unit);
    return unit;
}

static inline void SetDirs(VecFx32 *first, VecFx32 *second, const VecFx32 *v)
{
    VecFx32 unit;
    VEC_Normalize_01ff9f88(v, &unit);
    *first = unit;
    *second = *(VecFx32 *)&unit;
}

static inline void SetSides(VecFx32 *first, VecFx32 *second, const VecFx32 *a, const VecFx32 *b, BOOL vertical)
{
    VecFx32 unit;
    func_0204b9c8(&unit, a, b, vertical);
    *first = unit;
    *second = *(VecFx32 *)&unit;
}

static inline VecFx32 PointAtTime(s64 time, const VecFx32 *direction, const VecFx32 *origin)
{
    VecFx32 point;
    func_0204a7bc(time, direction, origin, &point);
    return point;
}

static inline VecFx32 GetSideAxis(const VecFx32 *a, const VecFx32 *b, BOOL vertical)
{
    VecFx32 side;
    func_0204b9c8(&side, a, b, vertical);
    return side;
}

static inline VecFx32 CrossFlat(const VecFx32 *a, const VecFx32 *b, BOOL flat)
{
    VecFx32 cross;
    if (!flat) {
        VEC_CrossProduct_01ff9ea8(a, b, &cross);
    } else {
        cross.x = -(fx32)(((fx64)a->z * b->y + 0x800) >> 12);
        cross.y = 0;
        cross.z = (fx32)(((fx64)a->x * b->y + 0x800) >> 12);
    }
    return cross;
}

static inline VecFx32 CrossWithBoxRow(const VecFx32 *a, const VecFx32 *b, const VecFx32 *row, BOOL flat)
{
    VecFx32 cross;
    if (!flat) {
        VEC_CrossProduct_01ff9ea8(a, b, &cross);
    } else {
        // Row 2 of the shifted box view is axes[k]
        cross.x = -(fx32)(((fx64)a->z * row[2].y + 0x800) >> 12);
        cross.y = 0;
        cross.z = (fx32)(((fx64)a->x * row[2].y + 0x800) >> 12);
    }
    return cross;
}

static inline VecFx32 CrossVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    VEC_CrossProduct_01ff9ea8(a, b, &cross);
    return cross;
}

static inline VecFx32 GetEdgeDirection(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge)
{
    VecFx32 direction;
    func_0203ed8c(box, axisA, axisB, edge, &direction);
    return direction;
}

static inline VecFx32 GetEdgeOffset(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge)
{
    VecFx32 offset;
    func_0203ee18(box, axisA, axisB, edge, &offset);
    return offset;
}

static inline VecFx32 GetCornerOffset(const CollisionBox *box, s32 signX, s32 signY, s32 signZ)
{
    VecFx32 offset;
    ComputeWeightedBasisSum_0203ed10(box, signX, signY, signZ, &offset);
    return offset;
}

static inline VecFx32 ScaleVec(VecFx32 vec, fx32 scale)
{
    func_0204a5e4(&vec, scale);
    return vec;
}

static inline VecFx32 DivideVec(VecFx32 vec, fx32 divisor)
{
    func_0204a6ac(&vec, divisor);
    return vec;
}

static inline VecFx32 ScaleUp(VecFx32 vec, fx32 scale, BOOL vertical)
{
    ScaleVecFx32ComponentsConditional_0204b6c4(&vec, scale, vertical);
    return vec;
}

static inline VecFx32 NegateUp(VecFx32 vec, fx32 sign, BOOL vertical)
{
    NegateVecComponentsConditional_0204b758(&vec, sign, vertical);
    return vec;
}

static inline VecFx32 FlipIfNegative(VecFx32 vec, fx32 sign)
{
    if (sign < 0) {
        NegateVecFx32_0204aa40(&vec);
    }
    return vec;
}

static inline VecFx32 MultAddVec(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 sum;
    VEC_MultAdd_01ffa09c(scale, v, add, &sum);
    return sum;
}

static inline VecFx32 RejectAlong(const VecFx32 *vec, const VecFx32 *axis, fx32 dot, BOOL vertical)
{
    VecFx32 projection;
    VecFx32 scaled;
    VecFx32 result;
    const VecFx32 *proj;
    scaled = *axis;
    ScaleVecFx32ComponentsConditional_0204b6c4(&scaled, dot, vertical);
    projection = scaled;
    proj = &projection;
    result = *vec;
    if (!vertical) {
        result.x -= proj->x;
        result.z -= proj->z;
    }
    result.y -= proj->y;
    return result;
}

static inline VecFx32 SubtractScaled(const VecFx32 *vec, const VecFx32 *axis, fx32 amount)
{
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;
    scaledAxis = *axis;
    func_0204a5e4(&scaledAxis, amount);
    projection = scaledAxis;
    VEC_Subtract_01ff9e3c(vec, &projection, &rejection);
    return rejection;
}

static inline const VecFx32 *NormalizedCross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 saved;
    VecFx32 copy;
    VecFx32 cross;
    VecFx32 unit;
    VEC_CrossProduct_01ff9ea8(a, b, &cross);
    copy = cross;
    VEC_Normalize_01ff9f88(&copy, &unit);
    saved = unit;
    return &saved;
}

static inline const VecFx32 *SubtractScaledRef(const VecFx32 *vec, const VecFx32 *axis, fx32 amount)
{
    VecFx32 saved;
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;
    scaledAxis = *axis;
    func_0204a5e4(&scaledAxis, amount);
    projection = scaledAxis;
    VEC_Subtract_01ff9e3c(vec, &projection, &rejection);
    saved = rejection;
    return &saved;
}

static inline Vec2Fx32 ScalePair(Vec2Fx32 pair, fx32 scale)
{
    ScalePairInPlace_0204a350(&pair, scale);
    return pair;
}

static inline const Vec2Fx32 *ScalePairInto(Vec2Fx32 *out, Vec2Fx32 pair, fx32 scale)
{
    ScalePairInPlace_0204a350(&pair, scale);
    *out = pair;
    return out;
}

static inline Vec2Fx32 AddPair(const Vec2Fx32 *a, const Vec2Fx32 *b)
{
    Vec2Fx32 sum;
    func_0204a2e0(a, b, &sum);
    return sum;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

static inline fx32 Abs(fx32 value)
{
    return value < 0 ? -value : value;
}

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800) >> 12);
}

BOOL SweepBoxAgainstCylinder_020434d0(CollisionBox **boxRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags, const VecFx32 *velocity, s8 j, fx32 cosine)
{
    CollisionBox *box = *boxRef;
    BOOL isCapsule = cylinderRef->kind == 3;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    BOOL vertical = cylinder->direction.x == 0 && cylinder->direction.z == 0;
    BOOL flat = box->flags & 1;
    BOOL bothVertical = vertical && flat;
    SweepResult result = MakeSweepResult();
    VecFx32 normal;
    VecFx32 center;
    VecFx32 diff;
    VecFx32 halfSegment;
    VecFx32 axis;
    VecFx32 dir;
    VecFx32 moved;
    VecFx32 side;
    VecFx32 cross;
    VecFx32 edgeDirection;
    VecFx32 edgeOffset;
    VecFx32 toEnd;
    VecFx32 rel;
    VecFx32 rej;
    VecFx32 inPlane;
    VecFx32 corner;
    VecFx32 toCorner;
    VecFx32 horiz;
    VecFx32 perp;
    VecFx32 binormal;
    VecFx32 tip;
    VecFx32 tipRel;
    VecFx32 centerBuf[1];
    VecFx32 dirRef[1];
    VecFx32 sideRef[1];
    const VecFx32 *horizRef;
    const VecFx32 *boxAxes;
    const VecFx32 *perpRef;
    const VecFx32 *tipRelRef;
    const VecFx32 *tipRef;
    s32 length;
    s32 halfLength;
    s8 i;
    s8 k;
    s8 edge;
    s32 axisA;
    s32 axisB;
    BOOL flatAxis;
    fx32 edgeDist;
    u8 end;
    s8 z;
    s8 x;
    s8 y;

    *centerBuf = func_0204b604(2, &cylinder->start, &cylinder->end);
    center = *centerBuf;
    diff = SubtractVec(&box->center, &center);
    halfSegment = HalveVec(SubtractVec(&cylinder->end, &cylinder->start));
    axis = cylinder->direction;
    SetDirs(dirRef, &dir, velocity);
    length = cylinder->length;
    halfLength = cylinder->length / 2;

    for (i = 0; i < 3; i++) {
        fx32 extent;
        normal = box->axes[i];
        extent = box->halfExtents[i];
        if (isCapsule) {
            if (bothVertical) {
                if (i == 1) {
                    extent += halfLength;
                }
            } else {
                fx32 projection = VEC_DotProduct_01ff9e6c(&halfSegment, &normal);
                if (projection < 0) {
                    projection = -projection;
                }
                extent += projection;
            }
            extent += cylinder->radius;
        } else if (bothVertical) {
            if (i == 1) {
                extent += halfLength;
            } else {
                extent += cylinder->radius;
            }
        } else {
            extent += ComputeDirectionalExtent_0203d718(cylinder, &axis, length, &normal);
        }
        if (!SweepIntervalOnAxis_0204774c(extent, VEC_DotProduct_01ff9e6c(&normal, &diff), &normal, 0, velocity, &result, NULL)) {
            return FALSE;
        }
    }

    if (bothVertical) {
        fx32 distY;
        fx32 distX;
        fx32 distZ;
        moved = PointAtTime(result.enterTime, velocity, &diff);
        distY = moved.y < 0 ? -moved.y : moved.y;
        distX = moved.x < 0 ? -moved.x : moved.x;
        distZ = moved.z < 0 ? -moved.z : moved.z;
        if ((distX < box->halfExtents[0]) + (distY < box->halfExtents[1] + halfLength) + (distZ < box->halfExtents[2]) >= 2) {
            goto done;
        }
    } else {
        for (j = 0; j < 3; j++) {
            if (!func_0204b918(&box->axes[j], &axis, &normal, vertical)) {
                fx32 radius;
                VEC_Normalize_01ff9f88(&normal, &normal);
                radius = cylinder->radius;
                if (!SweepIntervalOnAxis_0204774c(radius + ProjectBoxExtentSkipAxis_0203d568(box, &normal, j), VEC_DotProduct_01ff9e6c(&normal, &diff), &normal, 0, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
    }

    for (k = 0; k < 3; k++) {
        fx32 sideDist;
        axisA = (s8)((k + 1) % 3);
        axisB = (s8)((k + 2) % 3);
        flatAxis = flat && k == 1;
        SetSides(sideRef, &side, &dir, &box->axes[k], flatAxis);
        cross = CrossWithBoxRow(&side, &box->axes[k], (const VecFx32 *)box + (u32)k, flatAxis);
        sideDist = VEC_DotProduct_01ff9e6c(&side, &halfSegment);
        edge = 0;
        boxAxes = box->axes;
        for (; edge < 4; edge++) {
            edgeDirection = GetEdgeDirection(box, axisA, axisB, edge);
            edgeOffset = GetEdgeOffset(box, axisA, axisB, edge);
            edgeDist = VEC_DotProduct_01ff9e6c(&edgeOffset, &side);
            for (end = 0; end < 2; end++) {
                fx32 dist;
                fx32 gap;
                fx32 extent;
                toEnd = SubtractVec(&box->center, end == 0 ? &cylinder->start : &cylinder->end);
                dist = VEC_DotProduct_01ff9e6c(&side, &toEnd) - edgeDist;
                gap = dist < 0 ? -dist : dist;
                if (gap < 0) {
                    gap = 0;
                } else if (gap > cylinder->radius) {
                    gap = cylinder->radius;
                }
                if (isCapsule) {
                    rel = SubtractVec(&toEnd, &edgeOffset);
                    if (Abs(VEC_DotProduct_01ff9e6c(&cross, &rel)) > cylinder->radius) {
                        fx32 sideDot = VEC_DotProduct_01ff9e6c(&edgeDirection, &side);
                        fx32 crossDot = VEC_DotProduct_01ff9e6c(&edgeDirection, &cross);
                        s8 sideSign = sideDot >= 0 ? 1 : -1;
                        s8 crossSign = crossDot >= 0 ? 1 : -1;
                        fx32 ratio = FX_Div_01ff9c84(gap, cylinder->radius);
                        BlendVectorsBySqrtComplement_0204b59c(&side, &cross, ratio * sideSign, crossSign, &normal);
                    } else {
                        normal = SubtractScaled(&rel, &box->axes[k], VEC_DotProduct_01ff9e6c(&rel, &boxAxes[k]));
                        if (normal.x == 0 && normal.y == 0 && normal.z == 0) {
                            continue;
                        }
                    }
                    func_0204a9b4(&normal);
                    if (VEC_DotProduct_01ff9e6c(&edgeDirection, &normal) <= 0xb50) {
                        continue;
                    }
                    extent = cylinder->radius + Abs(VEC_DotProduct_01ff9e6c(&halfSegment, &normal));
                } else {
                    cosine = VEC_DotProduct_01ff9e6c(&axis, &boxAxes[k]);
                    rej = RejectAlong(&axis, &box->axes[k], cosine, flatAxis);
                    if (cosine > 0xff0 || cosine < -0xff0) {
                        continue;
                    }
                    {
                        Vec2Fx32 coords;
                        Vec2Fx32 sinCos;
                        Vec2Fx32 perpCoords;
                        Vec2Fx32 blended;
                        Vec2Fx32 alongCoords;
                        Vec2Fx32 alongPerp;
                        Vec2Fx32 planeCoords;
                        fx32 perpDot;
                        fx32 normalDot;
                        fx32 stretch;
                        fx32 scaledGap;

                        inPlane = cosine < 0xff0 ? Normalized(&rej) : *sideRef;
                        perpDot = VEC_DotProduct_01ff9e6c(&cross, &inPlane);
                        normalDot = VEC_DotProduct_01ff9e6c(&side, &inPlane);
                        planeCoords.x = normalDot;
                        planeCoords.y = perpDot;
                        coords = planeCoords;
                        if (cosine < 0) {
                            cosine = -cosine;
                        }
                        stretch = cosine > 0x10 ? FxMul(coords.x < 0 ? -coords.x : coords.x, FX_Div_01ff9c84(0x1000, cosine) - 0x1000) : 0;
                        scaledGap = gap + FxMul(gap, stretch);
                        if (scaledGap > cylinder->radius) {
                            scaledGap = cylinder->radius;
                        }
                        sinCos.x = FX_Div_01ff9c84(scaledGap * -Sign(dist), cylinder->radius);
                        sinCos.y = ComputeOneMinusSquareFraction_02049d6c(sinCos.x);
                        perpCoords.y = planeCoords.x;
                        perpCoords.x = planeCoords.y;
                        perpCoords.y = perpCoords.y * 0xFFFFFFFF;
                        blended = AddPair(ScalePairInto(&alongCoords, planeCoords, func_0204a390(&sinCos, &coords)), ScalePairInto(&alongPerp, perpCoords, FxMul(func_0204a390(&sinCos, &perpCoords), cosine)));
                        if (NormalizeVec2Fx_0204a460(&blended, &blended)) {
                            normal = *sideRef;
                        } else {
                            normal = ScaleVec(*sideRef, blended.x);
                            normal = MultAddVec(blended.y, &cross, &normal);
                            VEC_Normalize_01ff9f88(&normal, &normal);
                        }
                    }
                    if (VEC_DotProduct_01ff9e6c(&edgeDirection, &normal) >= -0xb50) {
                        continue;
                    }
                    extent = ComputeDirectionalExtent_0203d718(cylinder, &axis, length, &normal);
                    extent -= Abs(VEC_DotProduct_01ff9e6c(&halfSegment, &normal));
                }
                if (!SweepIntervalOnAxis_0204774c(extent + ProjectBoxExtent_0203d4d0(box, &normal), VEC_DotProduct_01ff9e6c(&normal, &diff), &normal, 2, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
    }

    for (x = -1; x <= 1; x += 2) {
        for (y = -1; y <= 1; y += 2) {
            for (z = -1; z <= 1; z += 2) {
                fx32 along;
                fx32 extent;
                corner = GetCornerOffset(box, x, y, z);
                toCorner = SubtractVec(&diff, &corner);
                along = VEC_DotProduct_01ff9e6c(&toCorner, &axis);
                if (Abs(along) < halfLength) {
                    if (Abs(VEC_DotProduct_01ff9e6c(&dir, &axis)) > 0xff0) {
                        fx32 mag;
                        horizRef = &SubtractVec(&toCorner, &ScaleUp(axis, along, vertical));
                        horiz = *horizRef;
                        mag = VEC_Mag_01ff9f28(&horiz);
                        if (mag < 0x10) {
                            normal = NegateUp(axis, along, vertical);
                        } else {
                            normal = DivideVec(*horizRef, mag);
                        }
                    } else {
                        s8 cornerSign;
                        s8 binormalSign;
                        fx32 proj;
                        fx32 ratio;
                        fx32 complement;
                        perpRef = NormalizedCross(&axis, &dir);
                        perp = *perpRef;
                        cornerSign = Sign(VEC_DotProduct_01ff9e6c(&perp, &corner));
                        proj = VEC_DotProduct_01ff9e6c(&toCorner, &perp);
                        if (proj * cornerSign < -cylinder->radius) {
                            continue;
                        }
                        ratio = proj * cornerSign < cylinder->radius ? FX_Div_01ff9c84(proj, cylinder->radius) : Sign(proj) << 12;
                        complement = ratio < 0x1000 ? ComputeOneMinusSquareFraction_02049d6c(ratio) : 0;
                        binormal = CrossFlat(&perp, &axis, vertical);
                        binormalSign = VEC_DotProduct_01ff9e6c(&toCorner, &binormal) >= 0 ? 1 : -1;
                        normal = ScaleVec(*perpRef, ratio);
                        if (complement != 0) {
                            normal = MultAddVec(binormalSign * complement, &binormal, &normal);
                        }
                    }
                    VEC_Normalize_01ff9f88(&normal, &normal);
                } else if (isCapsule) {
                    fx32 tipDot;
                    fx32 mag;
                    tipRef = &func_0204b834(halfLength * -Sign(along), &axis, &toCorner, vertical);
                    tip = *tipRef;
                    tipDot = VEC_DotProduct_01ff9e6c(&tip, &dir);
                    tipRelRef = SubtractScaledRef(&tip, dirRef, tipDot);
                    tipRel = *tipRelRef;
                    mag = VEC_Mag_01ff9f28(&tipRel);
                    if (mag < 0x10) {
                        normal = FlipIfNegative(*dirRef, tipDot);
                    } else {
                        fx32 ratio = mag < cylinder->radius ? FX_Div_01ff9c84(mag, cylinder->radius) : 0x1000;
                        fx32 complement = ratio < 0x1000 ? ComputeOneMinusSquareFraction_02049d6c(ratio) : 0;
                        normal = DivideVec(*tipRelRef, ratio < 0x1000 ? cylinder->radius : mag);
                        if (complement != 0) {
                            normal = MultAddVec(complement * Sign(tipDot), &dir, &normal);
                            VEC_Normalize_01ff9f88(&normal, &normal);
                        }
                    }
                } else {
                    continue;
                }
                if (VEC_DotProduct_01ff9e6c(&normal, &corner) > 0) {
                    extent = ProjectBoxExtent_0203d4d0(box, &normal);
                    if (isCapsule) {
                        extent += cylinder->radius + Abs(VEC_DotProduct_01ff9e6c(&normal, &halfSegment));
                    } else {
                        extent += ComputeDirectionalExtent_0203d718(cylinder, &axis, length, &normal);
                    }
                    if (!SweepIntervalOnAxis_0204774c(extent, VEC_DotProduct_01ff9e6c(&normal, &diff), &normal, 2, velocity, &result, NULL)) {
                        return FALSE;
                    }
                }
            }
        }
    }

    if (!isCapsule) {
        fx32 extent;
        normal = axis;
        extent = ProjectBoxExtent_0203d4d0(box, &normal);
        extent += ComputeDirectionalExtent_0203d718(cylinder, &axis, length, &normal);
        if (!SweepIntervalOnAxis_0204774c(extent, VEC_DotProduct_01ff9e6c(&normal, &diff), &normal, 0, velocity, &result, NULL)) {
            return FALSE;
        }
    }

done:
    return ResolveSweepContact_0204792c(&result, contact, flags, velocity);
}
