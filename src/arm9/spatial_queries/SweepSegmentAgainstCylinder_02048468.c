#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 halfLength;
    fx32 radius;
} CollisionCylinder;

typedef struct SegmentShapeRef {
    CollisionSegment *segment;
    u8 pad_04[0x18];
    s32 kind;
} SegmentShapeRef;

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

typedef struct CollisionDisc {
    VecFx32 center;
    fx32 radius;
    VecFx32 normal;
} CollisionDisc;

typedef struct CollisionLine {
    VecFx32 origin;
    VecFx32 direction;
} CollisionLine;

extern const VecFx32 data_02053438;
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 ComputeDirectionalExtent_0203d718(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern BOOL func_0203fc24(const VecFx32 *v);
extern VecFx32 func_0203ff74(const CollisionSegment *segment);
extern BOOL func_02040548(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);
extern BOOL func_020405b4(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);
extern VecFx32 ComputeVectorRejection_02040aec(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 func_02040fdc(const CollisionCylinder *cylinder);
extern BOOL func_0204792c(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern SweepResult func_02047cec(void);
extern VecFx32 SubtractVecFx32Out_02047d2c(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_02047d5c(fx32 extent, const VecFx32 *diff, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern fx32 func_02047dac(fx32 value);
extern VecFx32 AddVecFx32Out_02047f98(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NegateVecFx32Out_02047fc8(const VecFx32 *v);
extern VecFx32 NormalizeVectorOut_0204840c(const VecFx32 *v);
extern VecFx32 CrossProductOut_02048438(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_02048ac4(const VecFx32 *v);
extern s32 func_02048ad8(fx32 value);
extern VecFx32 func_02048af0(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 func_02048b30(const VecFx32 *v, fx32 scale);
extern s32 Max_02048b68(s32 a, s32 b);
extern fx32 func_02048b74(fx32 value);
extern fx32 Vec_DotSelf_02048bac(const VecFx32 *v);
extern void BlendVectorsBySqrtComplementPositive_02048bbc(VecFx32 *a, const VecFx32 *b, fx32 t, VecFx32 *out);
extern CollisionLine func_02048bd0(const VecFx32 *origin, const VecFx32 *direction);
extern VecFx32 func_02048c10(const VecFx32 *v, fx32 length);
extern void MultAddOut_02048c48(VecFx32 *dst, fx32 scale, const VecFx32 *v, const VecFx32 *add);
extern void func_0204970c(const VecFx32 *delta, const CollisionDisc *disc, const CollisionLine *line, const VecFx32 *normal, const VecFx32 *perp, const VecFx32 *velocity, fx32 gap, s8 sign, VecFx32 *axis);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_0204a9b4(VecFx32 *v);
extern BOOL func_0204a9e4(const VecFx32 *a, const VecFx32 *b, VecFx32 *cross);
extern VecFx32 func_0204ad4c(const VecFx32 *v);
extern VecFx32 func_0204aea8(const VecFx32 *v, const VecFx32 *normal);
extern VecFx32 func_0204b604(s32 count, ...);

BOOL SweepSegmentAgainstCylinder_02048468(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    u8 i;
    CollisionSegment *segment = segmentRef->segment;
    CollisionCylinder *cylinder = cylinderRef->cylinder;

    if (!(flags & 4)) {
        SegmentShapeRef swappedRef;
        CollisionSegment moved = *segment;
        moved.end = AddVecFx32Out_02047f98(&moved.end, velocity);
        swappedRef.segment = &moved;
        if (cylinderRef->kind == 3) {
            return func_02040548(&swappedRef, cylinderRef, contact, flags & 1);
        }
        return func_020405b4(&swappedRef, cylinderRef, contact, flags & 1);
    }
    {
        BOOL isCapsule = cylinderRef->kind == 3;
        SweepResult result = func_02047cec();
        VecFx32 axis;
        VecFx32 centerA = func_0204b604(2, &segment->start, &segment->end);
        VecFx32 centerB = func_0204b604(2, &cylinder->start, &cylinder->end);
        VecFx32 delta = SubtractVecFx32Out_02047d2c(&centerA, &centerB);
        VecFx32 halfA = func_0203ff74(segment);
        VecFx32 halfB = func_02040fdc(cylinder);
        VecFx32 dir = NormalizeVectorOut_0204840c(velocity);
        VecFx32 cross = CrossProductOut_02048438(&halfA, &halfB);
        BOOL parallel = func_02048ac4(&cross);

        if (parallel) {
            VecFx32 sideAxis;
            if (func_0204a9e4(&cylinder->direction, &dir, &sideAxis)) {
                axis = func_0204aea8(&delta, &cylinder->direction);
            } else {
                VecFx32 normal = NormalizeVectorOut_0204840c(&sideAxis);
                VecFx32 slide = func_0204aea8(&dir, &cylinder->direction);
                s32 sign = func_02048ad8(VEC_DotProduct_01ff9e6c(&slide, &delta));
                VecFx32 offset = func_02048af0(&delta, &normal);
                VecFx32 along = func_02048b30(&slide, sign * FX_Sqrt_01ff9cfc(Max_02048b68(func_02048b74(cylinder->radius) - Vec_DotSelf_02048bac(&offset), 0)));
                VEC_Add_01ff9e0c(&offset, &along, &axis);
                if (func_0203fc24(&axis)) {
                    axis = func_0204ad4c(&cylinder->direction);
                }
                func_0204a9b4(&axis);
            }
        } else {
            func_01ff9f88(&cross, &axis);
        }
        if (!func_02047d5c(cylinder->radius, &delta, &axis, 0, velocity, &result, NULL)) {
            return FALSE;
        }
        {
            VecFx32 dirA = segment->direction;
            VecFx32 dirB = cylinder->direction;
            fx32 halfLengthB = cylinder->halfLength;

            if (!parallel) {
                const VecFx32 *axes[2];
                const VecFx32 *halves[2];

                axes[0] = &dirA;
                axes[1] = &dirB;
                halves[0] = &halfA;
                halves[1] = &halfB;
                for (i = 0; i < 2; i++) {
                    u8 other = i ^ 1;
                    const VecFx32 *ownAxis = axes[i];
                    VecFx32 side = CrossProductOut_02048438(ownAxis, &dir);
                    fx32 extent;

                    if (func_02048ac4(&side)) {
                        VecFx32 rejA = ComputeVectorRejection_02040aec(&AddVecFx32Out_02047f98(&delta, &NegateVecFx32Out_02047fc8(halves[other])), ownAxis);
                        VecFx32 rejB = ComputeVectorRejection_02040aec(&AddVecFx32Out_02047f98(&delta, halves[other]), ownAxis);

                        if (VEC_Mag_01ff9f28(&rejA) < VEC_Mag_01ff9f28(&rejB)) {
                            axis = NormalizeVectorOut_0204840c(&rejA);
                        } else {
                            axis = NormalizeVectorOut_0204840c(&rejB);
                        }
                        extent = cylinder->radius;
                    } else {
                        VecFx32 unitSide = NormalizeVectorOut_0204840c(&side);
                        VecFx32 perp = CrossProductOut_02048438(&unitSide, ownAxis);
                        fx32 dist = VEC_DotProduct_01ff9e6c(&unitSide, &delta);
                        fx32 otherExtent = AbsDotProduct_0204a96c(halves[other], &unitSide);
                        fx32 gap = func_02047dac(dist) - otherExtent;

                        if (gap < 0) {
                            gap = 0;
                        } else if (gap > cylinder->radius) {
                            gap = cylinder->radius;
                        }
                        if (isCapsule || i == 1) {
                            BlendVectorsBySqrtComplementPositive_02048bbc(&unitSide, &perp, FX_Div_01ff9c84(gap * -func_02048ad8(dist), cylinder->radius), &axis);
                            extent = cylinder->radius + AbsDotProduct_0204a96c(&halfB, &axis);
                        } else {
                            CollisionDisc disc;

                            disc.radius = cylinder->radius;
                            disc.normal = dirB;
                            func_0204970c(&delta, &disc, &func_02048bd0(&data_02053438, &dirA), &unitSide, &perp, velocity, gap, -func_02048ad8(dist), &axis);
                            extent = ComputeDirectionalExtent_0203d718(cylinder, &dirB, halfLengthB * 2, &axis);
                        }
                    }
                    if (!func_02047d5c(extent + AbsDotProduct_0204a96c(&halfA, &axis), &delta, &axis, 2, velocity, &result, NULL)) {
                        return FALSE;
                    }
                }
            }
            if (isCapsule) {
                u8 a;
                u8 j;

                for (a = 0; a < 2; a++) {
                    VecFx32 pointA = (a == 0) ? segment->start : segment->end;

                    for (j = 0; j < 2; j++) {
                        VecFx32 pointB = (j == 0) ? cylinder->start : cylinder->end;
                        VecFx32 diff = SubtractVecFx32Out_02047d2c(&pointA, &pointB);
                        VecFx32 rej = ComputeVectorRejection_02040aec(&diff, &dir);
                        fx32 dist = VEC_Mag_01ff9f28(&rej);
                        fx32 ratio = dist < cylinder->radius ? FX_Div_01ff9c84(dist, cylinder->radius) : 0x1000;
                        fx32 height = ratio < 0x1000 ? ComputeOneMinusSquareFraction_02049d6c(ratio) : 0;
                        VecFx32 outward = dist > 0x10 ? func_02048c10(&rej, dist) : data_02053438;
                        s32 sign = func_02048ad8(VEC_DotProduct_01ff9e6c(&dir, &diff));

                        axis = func_02048b30(&outward, ratio);
                        if (height != 0) {
                            MultAddOut_02048c48(&axis, sign * height, &dir, &axis);
                        }
                        if ((a == 0 ? -1 : 1) * VEC_DotProduct_01ff9e6c(&axis, &segment->direction) < 0 &&
                            (j == 0 ? -1 : 1) * VEC_DotProduct_01ff9e6c(&axis, &cylinder->direction) > 0) {
                            func_01ff9f88(&axis, &axis);
                            if (!func_02047d5c(cylinder->radius, &diff, &axis, 2, velocity, &result, NULL)) {
                                return FALSE;
                            }
                        }
                    }
                }
            } else {
                fx32 extent;

                axis = dirB;
                extent = AbsDotProduct_0204a96c(&halfA, &axis);
                if (!func_02047d5c(extent + halfLengthB, &delta, &axis, 0, velocity, &result, NULL)) {
                    return FALSE;
                }
            }
        }
        return func_0204792c(&result, contact, flags, velocity);
    }
}
