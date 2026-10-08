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

typedef struct BoxShapeRef {
    CollisionBox *box;
} BoxShapeRef;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

typedef struct PlaneCoords {
    fx32 u;
    fx32 v;
} PlaneCoords;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

extern fx32 func_01ff9cfc(fx32 value);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern fx32 func_0203d4d0(const CollisionBox *box, const VecFx32 *axis);
extern fx32 func_0203d568(const CollisionBox *box, const VecFx32 *axis, u8 axisIndex);
extern fx32 ScaleDotProductFraction_0203d658(const VecFx32 *a, fx32 scale, const VecFx32 *b);
extern fx32 ComputeDirectionalExtent_0203d718(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern BOOL func_0203d854(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern BOOL func_0203d8b4(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern void func_0203d8fc(const PenetrationResult *result, void *contact, u32 flags);
extern void ComputeWeightedBasisSum_0203ed10(const CollisionBox *box, fx32 weightX, fx32 weightY, fx32 weightZ, VecFx32 *out);
extern void func_0203ed8c(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out);
extern void func_0203ee18(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void func_0204a6ac(VecFx32 *vec, fx32 divisor);
extern BOOL NormalizeUnlessDefault_0204a980(VecFx32 *vec);
extern VecFx32 func_0204b604(s32 count, ...);
extern void ScaleVecFx32ComponentsConditional_0204b6c4(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern VecFx32 func_0204b834(fx32 scale, const VecFx32 *axis, const VecFx32 *base, BOOL vertical);
extern BOOL func_0204b918(const VecFx32 *a, const VecFx32 *b, VecFx32 *out, BOOL vertical);
extern void func_0204b9c8(VecFx32 *out, const VecFx32 *a, const VecFx32 *b, BOOL vertical);
extern void func_0204bac4(VecFx32 *vec, const VecFx32 *axis, BOOL vertical);
extern VecFx32 func_0204bc78(const VecFx32 *vec, const VecFx32 *axis, BOOL vertical);

static inline PenetrationResult MakeEmptyResult(void)
{
    PenetrationResult result;
    result.depth = 0x7FFFFFFF;
    return result;
}

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract_01ff9e3c(a, b, &diff);
    return diff;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add_01ff9e0c(a, b, &sum);
    return sum;
}

static inline VecFx32 HalveVec(VecFx32 vec)
{
    vec.x >>= 1;
    vec.y >>= 1;
    vec.z >>= 1;
    return vec;
}

static inline VecFx32 DivideVec(VecFx32 vec, fx32 divisor)
{
    func_0204a6ac(&vec, divisor);
    return vec;
}

static inline VecFx32 ScaleVec(VecFx32 vec, fx32 scale)
{
    func_0204a5e4(&vec, scale);
    return vec;
}

static inline PlaneCoords MakeCoords(fx32 u, fx32 v)
{
    PlaneCoords coords;
    coords.u = u;
    coords.v = v;
    return coords;
}

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800) >> 12);
}

static inline VecFx32 MultAddVec(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 sum;
    VEC_MultAdd_01ffa09c(scale, v, add, &sum);
    return sum;
}

static inline VecFx32 NormalizeVecInto(const VecFx32 *vec)
{
    VecFx32 unit;
    func_01ff9f88(vec, &unit);
    return unit;
}

static inline VecFx32 NormalizedVec(const VecFx32 *vec)
{
    return NormalizeVecInto(vec);
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

static inline VecFx32 CrossWithBoxRow(const VecFx32 *a, const VecFx32 *b, const VecFx32 *boxRow, BOOL vertical)
{
    VecFx32 cross;
    if (!vertical) {
        VEC_CrossProduct_01ff9ea8(a, b, &cross);
    } else {
        // Row 2 of the shifted box view is axes[k]
        cross.x = -(fx32)(((fx64)a->z * boxRow[2].y + 0x800) >> 12);
        cross.y = 0;
        cross.z = (fx32)(((fx64)a->x * boxRow[2].y + 0x800) >> 12);
    }
    return cross;
}

static inline VecFx32 GetSideAxis(const VecFx32 *edgeAxis, const VecFx32 *axis, BOOL vertical)
{
    VecFx32 side;
    func_0204b9c8(&side, edgeAxis, axis, vertical);
    return side;
}

static inline VecFx32 ScaledAxis(const VecFx32 *axis, fx32 scale, BOOL vertical)
{
    VecFx32 scaled = *axis;
    ScaleVecFx32ComponentsConditional_0204b6c4(&scaled, scale, vertical);
    return scaled;
}

static inline void RejectInto(VecFx32 *out, const VecFx32 *vec, VecFx32 projection, BOOL vertical)
{
    const VecFx32 *proj = &projection;
    *out = *vec;
    if (!vertical) {
        out->x -= proj->x;
        out->z -= proj->z;
    }
    out->y -= proj->y;
}

static inline VecFx32 RejectAxis(const VecFx32 *vec, const VecFx32 *axis, BOOL vertical)
{
    VecFx32 result;
    RejectInto(&result, vec, ScaledAxis(axis, VEC_DotProduct_01ff9e6c(vec, axis), vertical), vertical);
    return result;
}

BOOL TestBoxAgainstCylinder_0203b704(BoxShapeRef *boxRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags)
{
    CollisionBox *box = boxRef->box;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    BOOL isCapsule = cylinderRef->kind == 3;
    BOOL vertical = cylinder->direction.x == 0 && cylinder->direction.z == 0;
    BOOL flatBox = box->flags & 1;
    BOOL bothVertical = vertical && flatBox;
    PenetrationResult result = MakeEmptyResult();
    VecFx32 center = func_0204b604(2, &cylinder->start, &cylinder->end);
    VecFx32 delta = SubtractVec(&box->center, &center);
    VecFx32 normal;
    VecFx32 halfSegment = HalveVec(SubtractVec(&cylinder->end, &cylinder->start));
    VecFx32 axis = cylinder->direction;
    s32 halfLength;
    s8 k;
    s8 edge;
    s32 axisA;
    s32 axisB;
    BOOL flatAxis;
    fx32 endDist;
    s8 signX;
    s8 signY;
    s32 length;
    BOOL startCloser;
    s8 i;
    const VecFx32 *boxRow;

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
        if (!func_0203d854(extent, VEC_DotProduct_01ff9e6c(&normal, &delta), &normal, 0, &result)) {
            return FALSE;
        }
    }

    if (bothVertical) {
        fx32 distY = delta.y < 0 ? -delta.y : delta.y;
        fx32 distX = delta.x < 0 ? -delta.x : delta.x;
        fx32 distZ = delta.z < 0 ? -delta.z : delta.z;
        if ((distX < box->halfExtents[0]) + (distY < box->halfExtents[1] + halfLength) + (distZ < box->halfExtents[2]) >= 2) {
            goto done;
        }
    } else {
        s8 j;
        for (j = 0; j < 3; j++) {
            if (!func_0204b918(&box->axes[j], &axis, &normal, vertical)) {
                func_01ff9f88(&normal, &normal);
                fx32 radius = cylinder->radius;
                if (!func_0203d854(radius + func_0203d568(box, &normal, j), VEC_DotProduct_01ff9e6c(&normal, &delta), &normal, 0, &result)) {
                    return FALSE;
                }
            }
        }
    }

    {
        for (k = 0; k < 3; k++) {
            axisA = (s8)((k + 1) % 3);
            axisB = (s8)((k + 2) % 3);
            flatAxis = FALSE;
            if (flatBox && k == 1) {
                flatAxis = TRUE;
            }
            edge = 0;
            boxRow = (const VecFx32 *)box + k;
            for (; edge < 4; edge++) {
                VecFx32 edgeDirection = GetEdgeDirection(box, axisA, axisB, edge);
                VecFx32 edgeOffset = GetEdgeOffset(box, axisA, axisB, edge);
                VecFx32 edgePoint = AddVec(&box->center, &edgeOffset);
                VecFx32 toStart = func_0204bc78(&SubtractVec(&edgePoint, &cylinder->start), &box->axes[k], flatAxis);
                VecFx32 toEnd = func_0204bc78(&SubtractVec(&edgePoint, &cylinder->end), &box->axes[k], flatAxis);
                s32 endSide = VEC_DotProduct_01ff9e6c(&toEnd, &axis) >= 0 ? 1 : -1;
                s32 startSide = VEC_DotProduct_01ff9e6c(&toStart, &axis) >= 0 ? 1 : -1;
                if (startSide == endSide) {
                    fx32 startDist = VEC_DotProduct_01ff9e6c(&toStart, &toStart);
                    endDist = VEC_DotProduct_01ff9e6c(&toEnd, &toEnd);
                    startCloser = startDist < endDist;
                    if (startCloser) {
                        startDist = func_01ff9cfc(startDist);
                    } else {
                        endDist = func_01ff9cfc(endDist);
                    }
                    normal = startCloser ? DivideVec(toStart, startDist) : DivideVec(toEnd, endDist);
                    if (VEC_DotProduct_01ff9e6c(&edgeDirection, &normal) < -0xB50) {
                        fx32 extent;
                        if (isCapsule) {
                            extent = cylinder->radius;
                        } else {
                            const VecFx32 side = GetSideAxis(&box->axes[k], &axis, vertical);
                            VecFx32 cross = CrossWithBoxRow(&side, &box->axes[k], boxRow, flatAxis);
                            fx32 cosine = VEC_DotProduct_01ff9e6c(&box->axes[k], &axis);
                            PlaneCoords coords = MakeCoords(VEC_DotProduct_01ff9e6c(&normal, &side), VEC_DotProduct_01ff9e6c(&normal, &cross));
                            if (cosine < 0) {
                                cosine = -cosine;
                            }
                            normal = ScaleVec(side, FX_Mul(coords.u, cosine));
                            normal = MultAddVec(coords.v, &cross, &normal);
                            if (normal.x == 0 && normal.y == 0 && normal.z == 0) {
                                continue;
                            }
                            extent = ScaleDotProductFraction_0203d658(&axis, cylinder->radius, &normal);
                        }
                        func_01ff9f88(&normal, &normal);
                        if (!func_0203d8b4(extent, startCloser ? startDist : endDist, &normal, 2, &result)) {
                            return FALSE;
                        }
                    }
                }
            }
        }
    }

    {
        s8 signZ;
        for (signX = -1; signX <= 1; signX += 2) {
            for (signY = -1; signY <= 1; signY += 2) {
                for (signZ = -1; signZ <= 1; signZ += 2) {
                    VecFx32 corner = GetCornerOffset(box, signX, signY, signZ);
                    const VecFx32 toCorner = SubtractVec(&delta, &corner);
                    fx32 along = VEC_DotProduct_01ff9e6c(&toCorner, &axis);
                    fx32 extent;
                    if ((along < 0 ? -along : along) < halfLength) {
                        normal = RejectAxis(&toCorner, &axis, vertical);
                        if (NormalizeUnlessDefault_0204a980(&normal)) {
                            func_0204bac4(&normal, &axis, vertical);
                        }
                    } else if (isCapsule) {
                        s32 sign = along == 0 ? 0 : along > 0 ? 1 : -1;
                        VecFx32 tip = func_0204b834(halfLength * -sign, &axis, &toCorner, vertical);
                        normal = NormalizedVec(&tip);
                    } else {
                        continue;
                    }
                    extent = func_0203d4d0(box, &normal);
                    if (isCapsule) {
                        fx32 projection = VEC_DotProduct_01ff9e6c(&normal, &halfSegment);
                        if (projection < 0) {
                            projection = -projection;
                        }
                        extent += cylinder->radius + projection;
                    } else {
                        extent += ComputeDirectionalExtent_0203d718(cylinder, &axis, length, &normal);
                    }
                    if (!func_0203d854(extent, VEC_DotProduct_01ff9e6c(&normal, &delta), &normal, 2, &result)) {
                        return FALSE;
                    }
                }
            }
        }
    }

    if (!isCapsule) {
        fx32 extent;
        normal = axis;
        extent = func_0203d4d0(box, &normal);
        extent += ComputeDirectionalExtent_0203d718(cylinder, &axis, length, &normal);
        if (!func_0203d854(extent, VEC_DotProduct_01ff9e6c(&normal, &delta), &normal, 0, &result)) {
            return FALSE;
        }
    }

done:
    func_0203d8fc(&result, contact, flags);
    return TRUE;
}
