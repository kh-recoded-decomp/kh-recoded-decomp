#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct SphereShapeRef {
    CollisionSphere *sphere;
} SphereShapeRef;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
} CylinderShapeRef;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern int Abs_0203f228(int value);
extern fx32 Vec_DotSelf_0203f258(const VecFx32 *v);
extern fx32 Square_0203f268(fx32 value);
extern VecFx32 DivideVecFx32_0203f2b0(const VecFx32 *v, fx32 divisor);
extern fx32 FX_DivQ27_0203f4d8(fx32 numer, fx32 denom);
extern VecFx32 ScaleVecFx32_0203f4fc(const VecFx32 *v, fx32 scale);
extern VecFx32 ComputeNormalizedCross_0203f548(const VecFx32 *v);
extern VecFx32 NormalizeVec_0203f580(const VecFx32 *src);
extern VecFx32 GetSegmentDirection_0203f950(const CollisionCylinder *cylinder);
extern VecFx32 AddVecFx32Into_0203f980(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NegateVecFx32Into_0203f9b0(const VecFx32 *src);
extern s32 Min_0203f9e0(s32 a, s32 b);
extern fx32 Hypot_0203f9ec(fx32 a, fx32 b);
extern fx32 NormalizeVec2Fx32_0204a3e4(Vec2Fx32 *vec);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);

BOOL TestSphereAgainstCylinder_0203f658(SphereShapeRef *sphereRef, CylinderShapeRef *cylinderRef, CollisionHit *hit, u32 flags)
{
    CollisionSphere *sphere = sphereRef->sphere;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    VecFx32 axis = GetSegmentDirection_0203f950(cylinder);
    fx32 length = func_01ffaff4(&axis, &axis);
    fx32 dotCenter = VEC_DotProduct_01ff9e6c(&axis, &sphere->center);
    fx32 dotStart = VEC_DotProduct_01ff9e6c(&axis, &cylinder->start);
    fx32 dotEnd = VEC_DotProduct_01ff9e6c(&axis, &cylinder->end);
    VecFx32 toCenter;
    fx32 sqDistance;

    if (dotCenter < dotStart - sphere->radius || dotCenter > dotEnd + sphere->radius) {
        return FALSE;
    }
    toCenter = AddVecFx32Into_0203f980(&cylinder->start, &ScaleVecFx32_0203f4fc(&axis, dotCenter - dotStart));
    VEC_Subtract_01ff9e3c(&toCenter, &sphere->center, &toCenter);
    sqDistance = Vec_DotSelf_0203f258(&toCenter);
    if ((dotCenter > dotStart) != (dotCenter > dotEnd)) {
        fx32 radiusSum = sphere->radius + cylinder->radius;
        if (sqDistance > Square_0203f268(radiusSum)) {
            return FALSE;
        }
        if (hit != NULL) {
            if (sqDistance != 0) {
                sqDistance = FX_Sqrt_01ff9cfc(sqDistance);
                hit->depth = radiusSum - sqDistance;
                hit->normal = DivideVecFx32_0203f2b0(&toCenter, sqDistance);
                if (!(flags & 1)) {
                    NegateVecFx32_0204aa40(&hit->normal);
                }
            } else {
                hit->depth = radiusSum;
                hit->normal = ComputeNormalizedCross_0203f548(&axis);
            }
            hit->kind = 3;
            hit->time = FX_DivQ27_0203f4d8(dotCenter - dotStart, length);
        } else {
            return TRUE;
        }
    } else if (hit != NULL) {
        hit->depth = 0x7FFFFFFF;
    }
    {
        fx32 offset = dotCenter - (dotStart + length / 2);
        fx32 absOffset = Abs_0203f228(offset);

        if (absOffset <= length / 2 + sphere->radius) {
            if (absOffset <= length / 2) {
                fx32 capDepth = length / 2 + sphere->radius - absOffset;
                if (hit->depth > capDepth) {
                    hit->depth = capDepth;
                    if (offset >= 0) {
                        hit->normal = axis;
                        hit->time = 0x8000000;
                    } else {
                        hit->normal = NegateVecFx32Into_0203f9b0(&axis);
                        hit->time = 0;
                    }
                    hit->kind = 0;
                    if (flags & 1) {
                        NegateVecFx32_0204aa40(&hit->normal);
                    }
                }
                return TRUE;
            } else {
                fx32 distStart = Abs_0203f228(dotCenter - dotStart);
                fx32 distEnd = Abs_0203f228(dotCenter - dotEnd);
                fx32 capDistance = Min_0203f9e0(distStart, distEnd);
                fx32 rimRadius = FX_Sqrt_01ff9cfc(Square_0203f268(sphere->radius) - Square_0203f268(capDistance));

                if (sqDistance > Square_0203f268(rimRadius + cylinder->radius)) {
                    return FALSE;
                }
                if (hit != NULL) {
                    fx32 distance = FX_Sqrt_01ff9cfc(sqDistance);
                    if (distance > cylinder->radius) {
                        fx32 excess = distance - cylinder->radius;
                        fx32 depth = sphere->radius - Hypot_0203f9ec(excess, capDistance);
                        if (hit->depth > depth) {
                            Vec2Fx32 edge;
                            hit->depth = depth;
                            edge.x = excess;
                            edge.y = capDistance;
                            NormalizeVec2Fx32_0204a3e4(&edge);
                            hit->normal = ScaleVecFx32_0203f4fc(&NormalizeVec_0203f580(&toCenter), -edge.x);
                            if (distEnd < distStart) {
                                VEC_Add_01ff9e0c(&hit->normal, &ScaleVecFx32_0203f4fc(&axis, edge.y), &hit->normal);
                            } else {
                                VEC_Add_01ff9e0c(&hit->normal, &ScaleVecFx32_0203f4fc(&axis, -edge.y), &hit->normal);
                            }
                        } else {
                            return TRUE;
                        }
                    } else {
                        fx32 depth = sphere->radius - capDistance;
                        if (hit->depth > depth) {
                            hit->depth = depth;
                            if (distEnd < distStart) {
                                hit->normal = axis;
                            } else {
                                hit->normal = NegateVecFx32Into_0203f9b0(&axis);
                            }
                        } else {
                            return TRUE;
                        }
                    }
                    if (flags & 1) {
                        NegateVecFx32_0204aa40(&hit->normal);
                    }
                    hit->kind = 3;
                    hit->time = distEnd < distStart ? 0x8000000 : 0;
                }
                return TRUE;
            }
        }
        return FALSE;
    }
}
