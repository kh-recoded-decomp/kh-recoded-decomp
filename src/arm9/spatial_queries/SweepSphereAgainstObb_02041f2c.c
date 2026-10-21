#pragma opt_loop_invariants off
#include "nitro/types.h"
#include "nitro/fx_types.h"

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

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct OrientedBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} OrientedBox;

extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void InitHitQuery_0203ac24(SweepResult *result);
extern fx32 GetObbProjectedRadius_0203d4d0(const OrientedBox *box, const VecFx32 *axis);
extern void GetBoxLocalPoint_0203ed10(const OrientedBox *box, fx32 x, fx32 y, fx32 z, VecFx32 *out);
extern void GetBoxEdgeDiagonal_0203ed8c(const OrientedBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out);
extern void GetBoxEdgeMidpointOffset_0203ee18(const OrientedBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out);
extern BOOL SweepIntervalOnAxis_0204774c(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern fx32 BlendVectorsBySqrtComplement_0204b59c(VecFx32 *a, const VecFx32 *b, fx32 t, s32 factor, VecFx32 *out);
extern void ScaleVecFx32ComponentsConditional_0204b6c4(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern void NegateVecComponentsConditional_0204b758(VecFx32 *vec, s32 sign, s32 skipHorizontal);
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

static inline void SetDirs(VecFx32 *first, VecFx32 *second, const VecFx32 *v, BOOL vertical)
{
    VecFx32 dir;
    NormalizeOrVerticalAxis_0204b8bc(v, &dir, vertical);
    *first = dir;
    *second = *(VecFx32 *)&dir;
}

static inline void SetOffsets(VecFx32 *first, VecFx32 *second, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract_01ff9e3c(a, b, &diff);
    *first = diff;
    *second = *(VecFx32 *)&diff;
}

static inline fx32 Abs(fx32 value)
{
    return value < 0 ? -value : value;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

static inline VecFx32 EdgeDiagonal(const OrientedBox *box, s32 axisA, s32 axisB, s32 edge)
{
    VecFx32 out;
    GetBoxEdgeDiagonal_0203ed8c(box, axisA, axisB, edge, &out);
    return out;
}

static inline VecFx32 EdgeMidpoint(const OrientedBox *box, s32 axisA, s32 axisB, s32 edge)
{
    VecFx32 out;
    GetBoxEdgeMidpointOffset_0203ee18(box, axisA, axisB, edge, &out);
    return out;
}

static inline VecFx32 LocalPoint(const OrientedBox *box, s32 x, s32 y, s32 z)
{
    VecFx32 out;
    GetBoxLocalPoint_0203ed10(box, x, y, z, &out);
    return out;
}

static inline VecFx32 NegatedCond(const VecFx32 *dir, fx32 sign, BOOL vertical)
{
    VecFx32 vec = *dir;
    NegateVecComponentsConditional_0204b758(&vec, sign, vertical);
    return vec;
}

static inline VecFx32 Normalized(const VecFx32 *v)
{
    VecFx32 out;
    VEC_NormalizeUnchecked_01ff9f88(v, &out);
    return out;
}

static inline VecFx32 Scaled(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&vec, scale);
    return vec;
}

static inline VecFx32 EdgeNormal(const VecFx32 *axis, const VecFx32 *dir, BOOL vertical)
{
    return GetNormalizedCross_0204b9c8(axis, dir, vertical);
}

static inline VecFx32 EdgeBinormal(const VecFx32 *normal, const VecFx32 *axis, BOOL flat)
{
    VecFx32 cross;
    if (!flat) {
        VEC_CrossProduct_01ff9ea8(normal, axis, &cross);
    } else {
        cross.x = -FxMul(normal->z, axis->y);
        cross.y = 0;
        cross.z = FxMul(normal->x, axis->y);
    }
    return cross;
}

static inline VecFx32 RemoveAlong(const VecFx32 *rel, const VecFx32 *dir, fx32 proj, BOOL vertical)
{
    VecFx32 along;
    VecFx32 scaled;
    VecFx32 perp;
    const fx32 *sub = (const fx32 *)&along;
    scaled = *dir;
    ScaleVecFx32ComponentsConditional_0204b6c4(&scaled, proj, vertical);
    along = scaled;
    perp = *rel;
    if (!vertical) {
        perp.x -= sub[0];
        perp.z -= sub[2];
    }
    perp.y -= sub[1];
    return perp;
}

static inline BOOL TestAxis(fx32 radius, fx32 extent, const VecFx32 *axis, const VecFx32 *diff, u8 feature, const VecFx32 *velocity, SweepResult *result)
{
    return SweepIntervalOnAxis_0204774c(extent + radius, VEC_DotProduct_01ff9e6c(axis, diff), axis, feature, velocity, result, NULL);
}

static inline BOOL TestProjectedAxis(const CollisionSphere *sphere, const OrientedBox *box, const VecFx32 *axis, const VecFx32 *diff, const VecFx32 *velocity, SweepResult *result)
{
    fx32 extent;
    s64 radius;
    extent = GetObbProjectedRadius_0203d4d0(box, axis);
    radius = sphere->radius;
    return SweepIntervalOnAxis_0204774c(extent + (fx32)radius, VEC_DotProduct_01ff9e6c(axis, diff), axis, 1, velocity, result, NULL);
}

BOOL SweepSphereAgainstObb_02041f2c(CollisionSphere **sphereRef, OrientedBox **boxRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    CollisionSphere *sphere = *sphereRef;
    OrientedBox *box = *boxRef;
    BOOL vertical = velocity->x == 0 && velocity->z == 0;
    fx32 sphereRadius;
    s32 aligned = box->flags & 1;
    fx32 extent;
    BOOL useAligned = vertical && aligned;
    VecFx32 *axisPtr;
    SweepResult result;
    VecFx32 diff;
    VecFx32 axis;
    VecFx32 dir;
    VecFx32 edgeNormal;
    VecFx32 binormal;
    VecFx32 edgeDiag;
    VecFx32 midpoint;
    VecFx32 corner;
    VecFx32 offset;
    VecFx32 side;
    VecFx32 moveDir[1];
    VecFx32 rel[1];
    s8 i;
    s8 j;
    s8 k;
    s8 x;
    s8 y;
    s8 z;

    result = MakeSweepResult();
    diff = VecSub(&sphere->center, &box->center);
    if (useAligned && Abs(diff.x) < box->halfExtents[0] && Abs(diff.z) < box->halfExtents[2]) {
        if (!TestAxis(sphere->radius, box->halfExtents[1], &box->axes[1], &diff, 0, velocity, &result)) {
            return FALSE;
        }
    } else {
        SetDirs(moveDir, &dir, velocity, vertical);
        axisPtr = &axis;
        for (i = 0; i < 3; i++) {
            *axisPtr = box->axes[i];
            extent = box->halfExtents[i];
            sphereRadius = sphere->radius;
            if (!SweepIntervalOnAxis_0204774c(extent + sphereRadius, VEC_DotProduct_01ff9e6c(axisPtr, &diff), axisPtr, 0, velocity, &result, NULL)) {
                return FALSE;
            }
        }
        for (j = 0; j < 3; j++) {
            s8 next = (j + 1) % 3;
            s8 prev = (j + 2) % 3;
            BOOL flat;
            fx32 dist;
            flat = aligned && j == 1;
            edgeNormal = EdgeNormal(&box->axes[j], &dir, vertical);
            binormal = EdgeBinormal(&edgeNormal, &box->axes[j], flat);
            dist = VEC_DotProduct_01ff9e6c(&edgeNormal, &diff);
            for (k = 0; k < 4; k++) {
                edgeDiag = EdgeDiagonal(box, next, prev, k);
                if (VEC_DotProduct_01ff9e6c(&edgeDiag, &dir) <= 0xb50) {
                    fx32 t;
                    midpoint = EdgeMidpoint(box, next, prev, k);
                    t = Abs(dist - VEC_DotProduct_01ff9e6c(&midpoint, &edgeNormal));
                    BlendVectorsBySqrtComplement_0204b59c(&edgeNormal, &binormal, Sign(dist) * (t < sphere->radius ? FX_Div_01ff9c84(t, sphere->radius) : 0x1000), -1, &axis);
                    VEC_NormalizeUnchecked_01ff9f88(&axis, &axis);
                    if (!TestProjectedAxis(sphere, box, &axis, &diff, velocity, &result)) {
                        return FALSE;
                    }
                }
            }
        }
        for (x = -1; x <= 1; x += 2) {
            for (y = -1; y <= 1; y += 2) {
                for (z = -1; z <= 1; z += 2) {
                    fx32 proj;
                    fx32 len;
                    corner = LocalPoint(box, x, y, z);
                    SetOffsets(rel, &offset, &diff, &corner);
                    proj = VEC_DotProduct_01ff9e6c(&offset, &dir);
                    side = RemoveAlong(rel, moveDir, proj, vertical);
                    len = VEC_Mag_01ff9f28(&side);
                    if (len < 0x10) {
                        axis = NegatedCond(moveDir, proj, vertical);
                    } else {
                        fx32 t;
                        fx32 s;
                        if (len < sphere->radius) {
                            t = FX_Div_01ff9c84(len, sphere->radius);
                        } else {
                            t = 0x1000;
                        }
                        if (t < 0x1000) {
                            s = ComputeOneMinusSquareFraction_02049d6c(t);
                        } else {
                            s = 0;
                        }
                        axis = Scaled(Normalized(&side), t);
                        if (s) {
                            axis = AddScaledDirection_0204b834(s * Sign(proj), &dir, &axis, vertical);
                        }
                        VEC_NormalizeUnchecked_01ff9f88(&axis, &axis);
                    }
                    if (!TestProjectedAxis(sphere, box, &axis, &diff, velocity, &result)) {
                        return FALSE;
                    }
                }
            }
        }
    }
    return ResolveSweepContact_0204792c(&result, contact, flags, velocity);
}
