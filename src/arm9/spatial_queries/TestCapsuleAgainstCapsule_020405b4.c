#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Capsule {
    VecFx32 base;
    u8 pad_0C[0x0C];
    VecFx32 axis;
    fx32 length;
    fx32 radius;
} Capsule;

typedef struct CollisionBody {
    Capsule *shape;
} CollisionBody;

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

extern BOOL func_02040ca4(CollisionBody *bodyA, CollisionBody *bodyB, CollisionHit *hit, u32 flags);
extern BOOL IsWithinDelta16_02040acc(fx32 a, fx32 b);
extern BOOL IsNotWithinDelta16_02040c8c(int a, int b);
extern VecFx32 SubtractVecFx32Into_0203f4a8(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 ComputeVectorRejection_02040aec(const VecFx32 *v, const VecFx32 *axis);
extern VecFx32 ComputeCrossProduct_02040500(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 CrossNormalized_0203fffc(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 ScaleVecFx32_0203f4fc(const VecFx32 *v, fx32 scale);
extern VecFx32 MultAddVecFx32Out_02040c58(fx32 scale, const VecFx32 *v, const VecFx32 *add);
extern VecFx32 ApplySignToVecFx32_02040c0c(const VecFx32 *v, int sign);
extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern Vec2Fx32 MakeVec2Fx32_02040530(fx32 x, fx32 y);
extern Vec2Fx32 ScaleAddVec2Fx32_02040b44(int scale, const Vec2Fx32 *dir, const Vec2Fx32 *origin);
extern int Abs_0203f228(int value);
extern int Sign_0203f240(fx32 value);
extern s64 Square_0203f268(fx32 value);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern int FixedPointMultiply12(fx32 left, fx32 right);
extern int FX_Div_0203f9ec(int numer, int denom);
extern fx32 Min_0203f9e0(fx32 a, fx32 b);
extern fx32 FX_DivQ27_0203f4d8(fx32 numer, fx32 denom);
extern s64 LongMul_02023d9c(s64 a, s64 b);
extern s64 LongDiv_02023ba4(s64 numer, s64 denom);

BOOL TestCapsuleAgainstCapsule_020405b4(CollisionBody *bodyA, CollisionBody *bodyB, CollisionHit *hit, u32 flags)
{
    Capsule *capB = bodyB->shape;
    Capsule *capA = bodyA->shape;
    fx32 lenA;
    fx32 lenB;
    fx32 dist;
    fx32 absDist;
    fx32 halfWidth;
    int py;
    fx32 px;
    fx32 lenDy;
    fx32 absQx;
    fx32 depth;
    fx32 edge;
    s8 signPy;
    s8 signDy;
    fx32 offY;
    fx32 x1;
    fx32 x2;
    fx32 dx;
    fx32 lenDx;
    fx32 dy;
    fx32 y;
    fx32 dirX;
    fx32 lengthA;

    if (flags & 2) {
        goto fallback;
    }
    lengthA = capA->length;
    lenA = 0;
    if (IsWithinDelta16_02040acc(lengthA, 0)) {
fallback:
        return func_02040ca4(bodyA, bodyB, hit, flags);
    }
    {
        VecFx32 dirA = capA->axis;
        VecFx32 dirB = capB->axis;
        VecFx32 normal;

        lenB = capB->length;
        if (IsWithinDelta16_02040acc(capA->length, lenA)) {
            dirA = SubtractVecFx32Into_0203f4a8(&capA->base, &capB->base);
            dirA = ComputeVectorRejection_02040aec(&dirA, &dirB);
            func_01ffaff4(&dirA, &dirA);
        } else {
            lenA = capA->length;
        }
        if (AbsDotProduct_0204a96c(&dirA, &dirB) < 0xff0) {
            normal = CrossNormalized_0203fffc(&dirB, &dirA);
        } else {
            normal = SubtractVecFx32Into_0203f4a8(&capA->base, &capB->base);
            normal = ComputeVectorRejection_02040aec(&normal, &dirB);
            func_01ffaff4(&normal, &normal);
        }
        dist = VEC_DotProduct_01ff9e6c(&normal, &capA->base) - VEC_DotProduct_01ff9e6c(&normal, &capB->base);
        absDist = Abs_0203f228(dist);
        if (absDist > capB->radius) {
            return FALSE;
        }
        {
            VecFx32 side = ComputeCrossProduct_02040500(&normal, &dirB);
            VecFx32 relPos = SubtractVecFx32Into_0203f4a8(&capA->base, &capB->base);
            Vec2Fx32 p = MakeVec2Fx32_02040530(VEC_DotProduct_01ff9e6c(&relPos, &dirB), VEC_DotProduct_01ff9e6c(&relPos, &side));
            Vec2Fx32 d = MakeVec2Fx32_02040530(VEC_DotProduct_01ff9e6c(&dirA, &dirB), VEC_DotProduct_01ff9e6c(&dirA, &side));
            BOOL crosses;

            halfWidth = FX_Sqrt_01ff9cfc((fx32)(Square_0203f268(capB->radius) - Square_0203f268(dist)));
            dy = d.y;
            lenDy = FixedPointMultiply12(lenA, dy);
            py = p.y;
            crosses = (py >= 0) != (py + lenDy >= 0);
            if (crosses) {
                x1 = p.x + (fx32)((s64)py * d.x / -dy);
                if (x1 < 0 || x1 > lenB) {
                    crosses = FALSE;
                }
            }
            px = p.x;
            if (px >= 0 && px <= lenB && py >= -halfWidth && py <= halfWidth) {
                Vec2Fx32 q = ScaleAddVec2Fx32_02040b44(lenA, &d, &p);
                if (!crosses && (q.x < 0 || q.x > lenB || q.y < -halfWidth || q.y > halfWidth)) {
                    return FALSE;
                }
                if (hit == NULL) {
                    return TRUE;
                }
                absQx = Abs_0203f228(q.x);
                if (crosses) {
                    depth = capB->radius - absDist;
                } else {
                    depth = capB->radius - FX_Div_0203f9ec(q.y, dist);
                }
                edge = Min_0203f9e0(absQx, lenB - absQx);
                if (depth < edge) {
                    hit->depth = depth;
                    if (crosses) {
                        hit->normal = ApplySignToVecFx32_02040c0c(&normal, Sign_0203f240(dist));
                        hit->kind = 0;
                    } else {
                        hit->normal = ScaleVecFx32_0203f4fc(&normal, dist);
                        hit->normal = MultAddVecFx32Out_02040c58(q.y, &side, &hit->normal);
                        func_01ff9f88(&hit->normal, &hit->normal);
                        hit->kind = 2;
                        if (flags & 1) {
                            NegateVecFx32_0204aa40(&hit->normal);
                        }
                    }
                } else {
                    hit->depth = edge;
                    hit->normal = ApplySignToVecFx32_02040c0c(&dirB, Sign_0203f240(q.x - lenB / 2));
                    hit->kind = 0;
                    if (flags & 1) {
                        NegateVecFx32_0204aa40(&hit->normal);
                    }
                }
                hit->time = 0;
                return TRUE;
            }
            if (IsNotWithinDelta16_02040c8c(dy, 0)) {
                signPy = Sign_0203f240(py);
                signDy = Sign_0203f240(dy);

                if (signPy != signDy) {
                    offY = py - halfWidth * signPy;

                    if (lenDy * signDy >= Abs_0203f228(offY)) {
                        x2 = px + (fx32)((s64)offY * d.x / -dy);

                        if (x2 >= 0 && x2 <= lenB) {
                            if (hit != NULL) {
                                if (crosses) {
                                    hit->depth = capB->radius - absDist;
                                    hit->normal = ApplySignToVecFx32_02040c0c(&normal, Sign_0203f240(dist));
                                    hit->kind = 0;
                                } else {
                                    Vec2Fx32 q = ScaleAddVec2Fx32_02040b44(lenA, &d, &p);

                                    hit->depth = capB->radius - FX_Div_0203f9ec(q.y, dist);
                                    hit->normal = ScaleVecFx32_0203f4fc(&normal, dist);
                                    hit->normal = MultAddVecFx32Out_02040c58(q.y, &side, &hit->normal);
                                    func_01ff9f88(&hit->normal, &hit->normal);
                                    hit->kind = 2;
                                }
                                if (flags & 1) {
                                    NegateVecFx32_0204aa40(&hit->normal);
                                }
                                hit->time = Abs_0203f228(FX_DivQ27_0203f4d8(offY, lenDy));
                            }
                            return TRUE;
                        }
                    }
                }
            }
            {
                dx = d.x;
                if ((dx >= 0) == (px >= 0)) {
                    return FALSE;
                }
                px = dx < 0 ? px - lenB : px;
                lenDx = FixedPointMultiply12(lenA, dx);
                if (Abs_0203f228(lenDx) >= Abs_0203f228(px)) {
                    y = py + (fx32)((s64)px * dy / -dx);
                    if (y >= -halfWidth && y <= halfWidth) {
                        if (hit != NULL) {
                            dirX = d.x;
                            hit->depth = FixedPointMultiply12(lenA, Abs_0203f228(dirX)) - Abs_0203f228(px);
                            hit->normal = ApplySignToVecFx32_02040c0c(&dirB, -Sign_0203f240(dirX));
                            hit->kind = 0;
                            if (flags & 1) {
                                NegateVecFx32_0204aa40(&hit->normal);
                            }
                            hit->time = Abs_0203f228(FX_DivQ27_0203f4d8(px, lenDx));
                        }
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}
