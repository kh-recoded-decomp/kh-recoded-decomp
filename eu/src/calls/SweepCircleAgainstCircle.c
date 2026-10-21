#include "nitro/types.h"
#include "nitro/fx_types.h"

/* One rim of a cylinder: the cap centre, the radius and the axis. */
typedef struct CylinderRim {
    VecFx32 point;
    fx32 radius;
    VecFx32 axis;
} CylinderRim;

typedef struct Basis3x3 {
    VecFx32 row[3];
} Basis3x3;

typedef s64 (*ComponentFunc)(s32 value);

extern fx32 FX_Mul(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_Sqrt(fx32 value);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void SubtractVecFx32Out(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern void func_0204800c(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern void BuildMatrix33_020495cc(Basis3x3 *out, const VecFx32 *forward, const VecFx32 *up);
extern void TransformVectorByBasisOut_0204960c(VecFx32 *out, const VecFx32 *vec, const Basis3x3 *basis);
extern void func_0204963c(VecFx32 *out, fx32 x, fx32 y, fx32 z);
extern void func_0204966c(VecFx32 *out, const VecFx32 *vec, ComponentFunc func);
extern s64 SquareFx32_02048b88(s32 value);
extern s64 MulFx64ByFx32(s64 a, s32 b);
extern s64 DivFx64Shifted(s64 numerator, s64 denominator);
extern void SolveQuartic(fx32 cubic, fx32 quadratic, fx32 linear, s64 constant, fx32 *roots);
extern int MinOfArray(int count, int *values);
extern void MultAddOut(VecFx32 *out, fx32 scale, const VecFx32 *vec, const VecFx32 *add);
extern void func_02048b44(VecFx32 *out, const VecFx32 *vec, fx32 scale);
extern int SignOf(int value);
extern void CrossProductOut(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;

    SubtractVecFx32Out(&out, a, b);
    return out;
}

static inline VecFx32 VecPerp(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;

    func_0204800c(&out, a, b);
    return out;
}

static inline Basis3x3 MakeBasis(const VecFx32 *forward, const VecFx32 *up)
{
    Basis3x3 out;

    BuildMatrix33_020495cc(&out, forward, up);
    return out;
}

static inline VecFx32 ToBasis(const VecFx32 *vec, const Basis3x3 *basis)
{
    VecFx32 out;

    TransformVectorByBasisOut_0204960c(&out, vec, basis);
    return out;
}

static inline VecFx32 Rotated(const VecFx32 *vec)
{
    VecFx32 out;

    func_0204963c(&out, vec->y, vec->z, vec->x);
    return out;
}

static inline VecFx32 Squared(const VecFx32 *vec)
{
    VecFx32 out;

    func_0204966c(&out, vec, SquareFx32_02048b88);
    return out;
}

static inline VecFx32 MultAdd(fx32 scale, const VecFx32 *vec, const VecFx32 *add)
{
    VecFx32 out;

    MultAddOut(&out, scale, vec, add);
    return out;
}

static inline VecFx32 Cross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;

    CrossProductOut(&out, a, b);
    return out;
}

/*
 * Earliest time at which two circles (cylinder rims) moving apart by `dir` touch: both rims are
 * expressed in each other's frame, the contact condition becomes a quartic in time whose roots
 * go to `roots`, and for the earliest root the contact point on rim A gives the contact normal.
 * Returns 0x7fffffff when the rims never touch.
 */
fx32 SweepCircleAgainstCircle(const VecFx32 *dir, const CylinderRim *rimA, const CylinderRim *rimB, fx32 *roots,
                              VecFx32 *normal)
{
    VecFx32 offset;
    VecFx32 commonAxis;
    VecFx32 perpA;
    VecFx32 perpB;
    Basis3x3 basisA;
    Basis3x3 basisB;
    VecFx32 dirInA;
    VecFx32 dirInB;
    VecFx32 offsetInA;
    VecFx32 offsetInB;
    VecFx32 perpAInB;
    VecFx32 perpBInA;
    VecFx32 dirA;
    VecFx32 dirB;
    VecFx32 offA;
    VecFx32 offB;
    VecFx32 perpAB;
    VecFx32 perpBA;
    VecFx32 dirASq;
    VecFx32 dirBSq;
    VecFx32 offASq;
    VecFx32 offBSq;
    VecFx32 perpABSq;
    VecFx32 perpBASq;
    VecFx32 point;
    VecFx32 onRim;
    VecFx32 delta;
    VecFx32 crossA;
    VecFx32 crossB;
    fx32 radiusA;
    fx32 radiusB;
    fx32 dirTermA;
    fx32 dirTermB;
    fx32 mixTermA;
    fx32 mixTermB;
    fx32 offTermA;
    fx32 b;
    fx32 c;
    fx32 crossTerm;
    fx32 radiusTerm;
    fx32 cubicNum;
    fx32 quadraticNum;
    fx32 time;
    VecFx32 *contact = &onRim;
    fx32 offAx;
    fx32 offAz;
    fx32 offBz;
    fx32 dirAy;
    fx32 offAy;
    fx32 negMixTermB;
    fx32 negDirTermB;
    fx32 perpBAz;
    fx32 perpBAx;
    fx32 slopeB;
    fx32 slopeA;
    fx32 slopeBSq;
    fx32 slopeASq;
    fx32 dirAx;
    fx32 dirAz;
    fx32 dirBx;
    fx32 dirBz;
    fx32 offBx;
    fx32 dirASqY;
    fx32 offASqY;
    fx32 a;
    fx32 offTermB;
    s64 leading;
    fx32 linearNum;
    fx32 constantNum;

    offset = VecSub(&rimA->point, &rimB->point);
    commonAxis = VecPerp(&rimA->axis, &rimB->axis);
    perpA = VecPerp(&commonAxis, &rimA->axis);
    perpB = VecPerp(&commonAxis, &rimB->axis);
    basisA = MakeBasis(&rimA->axis, &commonAxis);
    basisB = MakeBasis(&rimB->axis, &commonAxis);
    dirInA = ToBasis(dir, &basisA);
    dirInB = ToBasis(dir, &basisB);
    offsetInA = ToBasis(&offset, &basisA);
    offsetInB = ToBasis(&offset, &basisB);
    perpAInB = ToBasis(&perpA, &basisB);
    perpBInA = ToBasis(&perpB, &basisA);
    dirA = Rotated(&dirInA);
    dirB = Rotated(&dirInB);
    offA = Rotated(&offsetInA);
    offB = Rotated(&offsetInB);
    perpAB = Rotated(&perpAInB);
    perpBA = Rotated(&perpBInA);
    radiusA = rimA->radius;
    radiusB = rimB->radius;
    dirASq = Squared(&dirA);
    dirBSq = Squared(&dirB);
    offASq = Squared(&offA);
    offBSq = Squared(&offB);
    perpABSq = Squared(&perpAB);
    perpBASq = Squared(&perpBA);

    slopeB = FX_Div(perpAB.x, perpAB.z);
    perpBAz = perpBA.z;
    perpBAx = perpBA.x;
    slopeA = FX_Div(perpBAx, perpBAz);
    slopeBSq = FX_Div(perpABSq.x, perpABSq.z);
    slopeASq = FX_Div(perpBASq.x, perpBASq.z);
    dirAz = dirA.z;
    dirAx = dirA.x;
    dirTermA = FX_Mul(dirASq.z, slopeASq) + (dirASq.x - (FX_Mul(FX_Mul(dirAx, dirAz), slopeA) << 1));
    dirBz = dirB.z;
    dirBx = dirB.x;
    dirTermB = FX_Mul(dirBSq.z, slopeBSq) + (dirBSq.x - (FX_Mul(FX_Mul(dirBx, dirBz), slopeB) << 1));
    offAz = offA.z;
    offAx = offA.x;
    mixTermA = (FX_Mul(FX_Mul(offAz, dirAz), slopeA) << 1) +
               ((FX_Mul(offAx, dirAx) << 1) - (FX_Mul(FX_Mul(offAx, dirAz) + FX_Mul(dirAx, offAz), slopeA) << 1));
    offBz = offB.z;
    offBx = offB.x;
    mixTermB = (FX_Mul(FX_Mul(offBz, dirBz), slopeB) << 1) +
               ((FX_Mul(offBx, dirBx) << 1) - (FX_Mul(FX_Mul(offBx, dirBz) + FX_Mul(dirBx, offBz), slopeB) << 1));
    offTermA = FX_Mul(offASq.z, slopeASq) + (offASq.x - (FX_Mul(FX_Mul(offAx, offAz), slopeA) << 1));
    offTermB = FX_Mul(offBSq.z, slopeBSq) + (offBSq.x - (FX_Mul(FX_Mul(offBx, offBz), slopeB) << 1));
    dirASqY = dirASq.y;
    a = (s64)((dirTermB - dirTermA) - dirASqY);
    dirAy = dirA.y;
    offAy = offA.y;
    b = (mixTermB - mixTermA) - (FX_Mul(offAy, dirAy) << 1);
    offASqY = offASq.y;
    c = offTermB + (((fx32)SquareFx32_02048b88(radiusA) - (fx32)SquareFx32_02048b88(radiusB)) - offTermA) - offASqY;
    crossTerm = FX_Mul(offAy, dirAy) << 1;
    radiusTerm = (fx32)SquareFx32_02048b88(radiusB) - offTermB;
    leading = MulFx64ByFx32((s64)a << 20, a);
    leading -= MulFx64ByFx32((s64)dirASqY << 20, -dirTermB) << 2;
    negDirTermB = -(s32)dirTermB;
    negMixTermB = -mixTermB;
    cubicNum = (FX_Mul(a, b) << 1) - ((FX_Mul(dirASqY, negMixTermB) + FX_Mul(crossTerm, negDirTermB)) << 2);
    quadraticNum = ((fx32)SquareFx32_02048b88(b) + (FX_Mul(a, c) << 1)) -
                   ((FX_Mul(offASqY, negDirTermB) + (FX_Mul(dirASqY, radiusTerm) + FX_Mul(crossTerm, negMixTermB)))
                    << 2);
    linearNum = (FX_Mul(b, c) << 1) - ((FX_Mul(crossTerm, radiusTerm) + FX_Mul(offASqY, negMixTermB)) << 2);
    constantNum = (fx32)SquareFx32_02048b88(c) - (FX_Mul(offASqY, radiusTerm) << 2);
    SolveQuartic(DivFx64Shifted(cubicNum, leading), DivFx64Shifted(quadraticNum, leading),
                 DivFx64Shifted(linearNum, leading), DivFx64Shifted(constantNum, leading), roots);
    time = MinOfArray(12, roots);
    if (time != 0x7fffffff) {
        fx32 along;
        int side;

        point = MultAdd(time, dir, &offset);
        along = VEC_DotProduct(&point, &basisA.row[1]) -
                FX_Div(FX_Mul(VEC_DotProduct(&point, &basisA.row[0]), perpBAx), perpBAz);
        func_02048b44(contact, &basisA.row[1], along);
        side = SignOf(VEC_DotProduct(&point, &commonAxis));
        MultAddOut(contact, side * FX_Sqrt((fx32)SquareFx32_02048b88(radiusA) - (fx32)SquareFx32_02048b88(along)),
                   &commonAxis, contact);
        SubtractVecFx32Out(&delta, contact, &point);
        crossA = Cross(contact, &rimA->axis);
        crossB = Cross(&delta, &rimB->axis);
        *normal = VecPerp(&crossA, &crossB);
        VEC_Normalize(normal, normal);
    }
    return time;
}
