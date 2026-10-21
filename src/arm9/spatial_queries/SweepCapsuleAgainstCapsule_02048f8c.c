#pragma opt_common_subs off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 row[3];
} Basis3x3;

typedef struct {
    VecFx32 pos;
    fx32 radius;
    VecFx32 dir;
} Capsule;

extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern int FixedPointMultiply12(int left, int right);
extern void SubtractVecFx32Out_02047d2c(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern void func_02047ff8(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern void CrossProductOut_02048438(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern int SignOf_02048ad8(int value);
extern void func_02048b30(VecFx32 *out, const VecFx32 *v, fx32 scale);
extern fx32 SquareFx32_02048b74(fx32 value);
extern void MultAddOut_02048c48(VecFx32 *dst, fx32 scale, const VecFx32 *v, const VecFx32 *add);
extern void BuildMatrix33_020495b8(Basis3x3 *out, const VecFx32 *first, const VecFx32 *second);
extern void TransformVectorByBasisOut_020495f8(VecFx32 *dst, const VecFx32 *vec, const Basis3x3 *basis);
extern void func_02049628(VecFx32 *out, fx32 x, fx32 y, fx32 z);
extern void func_02049658(VecFx32 *out, const VecFx32 *v, fx32 (*op)(fx32));
extern s64 MulFx64ByFx32_02049690(s64 a, s32 b);
extern s64 DivFx64Shifted_020496b4(s64 numer, s64 denom);
extern void func_0204c6c0(fx32 c3, fx32 c2, fx32 c1, s64 c0, fx32 *roots);
extern int MinOfArray_020496d8(int count, fx32 *values);

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    SubtractVecFx32Out_02047d2c(&out, a, b);
    return out;
}

static inline VecFx32 VecOp(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    func_02047ff8(&out, a, b);
    return out;
}

static inline VecFx32 VecCross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    CrossProductOut_02048438(&out, a, b);
    return out;
}

static inline VecFx32 VecMultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 out;
    MultAddOut_02048c48(&out, scale, v, add);
    return out;
}

static inline Basis3x3 MakeBasis(const VecFx32 *first, const VecFx32 *second)
{
    Basis3x3 out;
    BuildMatrix33_020495b8(&out, first, second);
    return out;
}

static inline VecFx32 ToBasis(const VecFx32 *vec, const Basis3x3 *basis)
{
    VecFx32 out;
    TransformVectorByBasisOut_020495f8(&out, vec, basis);
    return out;
}

static inline VecFx32 Rotate(fx32 x, fx32 y, fx32 z)
{
    VecFx32 out;
    func_02049628(&out, x, y, z);
    return out;
}

static inline VecFx32 MapVec(const VecFx32 *v, fx32 (*op)(fx32))
{
    VecFx32 out;
    func_02049658(&out, v, op);
    return out;
}

#define MUL FixedPointMultiply12
#define SQ SquareFx32_02048b74

int SweepCapsuleAgainstCapsule_02048f8c(const VecFx32 *velocity, Capsule *capA, Capsule *capB, fx32 *roots, VecFx32 *outNormal)
{
    VecFx32 diff;
    VecFx32 axis;
    VecFx32 crossA;
    VecFx32 crossB;
    Basis3x3 basisA;
    Basis3x3 basisB;
    VecFx32 velInA;
    VecFx32 velInB;
    VecFx32 diffInA;
    VecFx32 diffInB;
    VecFx32 crossAInB;
    VecFx32 crossBInA;
    VecFx32 a;
    VecFx32 b;
    VecFx32 c;
    VecFx32 d;
    VecFx32 e;
    VecFx32 f;
    VecFx32 a2;
    VecFx32 b2;
    VecFx32 c2;
    VecFx32 d2;
    VecFx32 e2;
    VecFx32 f2;
    VecFx32 point;
    VecFx32 contact;
    VecFx32 offset;
    VecFx32 armA;
    VecFx32 armB;
    fx32 radiusA;
    fx32 radiusB;
    fx32 ratioE;
    fx32 ratioF;
    fx32 ratioE2;
    fx32 ratioF2;
    fx32 termA;
    fx32 termB;
    fx32 termAC;
    fx32 termBD;
    fx32 termC;
    fx32 termD;
    fx32 coef4;
    fx32 coef3;
    fx32 coef2;
    fx32 crossTerm;
    fx32 restB;
    fx32 k3;
    fx32 k2;
    fx32 k1;
    fx32 k0;
    s64 denom;
    int result;

    diff = VecSub(&capA->pos, &capB->pos);
    axis = VecOp(&capA->dir, &capB->dir);
    crossA = VecOp(&axis, &capA->dir);
    crossB = VecOp(&axis, &capB->dir);
    basisA = MakeBasis(&capA->dir, &axis);
    basisB = MakeBasis(&capB->dir, &axis);
    velInA = ToBasis(velocity, &basisA);
    velInB = ToBasis(velocity, &basisB);
    diffInA = ToBasis(&diff, &basisA);
    diffInB = ToBasis(&diff, &basisB);
    crossAInB = ToBasis(&crossA, &basisB);
    crossBInA = ToBasis(&crossB, &basisA);
    a = Rotate(velInA.y, velInA.z, velInA.x);
    b = Rotate(velInB.y, velInB.z, velInB.x);
    c = Rotate(diffInA.y, diffInA.z, diffInA.x);
    d = Rotate(diffInB.y, diffInB.z, diffInB.x);
    e = Rotate(crossAInB.y, crossAInB.z, crossAInB.x);
    f = Rotate(crossBInA.y, crossBInA.z, crossBInA.x);
    radiusA = capA->radius;
    radiusB = capB->radius;
    a2 = MapVec(&a, SQ);
    b2 = MapVec(&b, SQ);
    c2 = MapVec(&c, SQ);
    d2 = MapVec(&d, SQ);
    e2 = MapVec(&e, SQ);
    f2 = MapVec(&f, SQ);

    {
    fx32 cx;
    fx32 cz;
    fx32 dz;
    fx32 ay;
    fx32 cy;
    fx32 negBD;
    fx32 negB;
    fx32 fz;
    fx32 fx;
    fx32 ax;
    fx32 az;
    fx32 bx;
    fx32 bz;
    fx32 dx;
    fx32 a2y;
    fx32 c2y;

    ratioE = FX_Div_01ff9c84(e.x, e.z);
    fz = f.z;
    fx = f.x;
    ratioF = FX_Div_01ff9c84(fx, fz);
    ratioE2 = FX_Div_01ff9c84(e2.x, e2.z);
    ratioF2 = FX_Div_01ff9c84(f2.x, f2.z);

    az = a.z;
    ax = a.x;
    termA = MUL(a2.z, ratioF2) + (a2.x - 2 * MUL(MUL(ax, az), ratioF));
    bz = b.z;
    bx = b.x;
    termB = MUL(b2.z, ratioE2) + (b2.x - 2 * MUL(MUL(bx, bz), ratioE));
    cz = c.z;
    cx = c.x;
    termAC = 2 * MUL(MUL(cz, az), ratioF) + (2 * MUL(cx, ax) - 2 * MUL(MUL(cx, az) + MUL(ax, cz), ratioF));
    dz = d.z;
    dx = d.x;
    termBD = 2 * MUL(MUL(dz, bz), ratioE) + (2 * MUL(dx, bx) - 2 * MUL(MUL(dx, bz) + MUL(bx, dz), ratioE));
    termC = MUL(c2.z, ratioF2) + (c2.x - 2 * MUL(MUL(cx, cz), ratioF));
    termD = MUL(d2.z, ratioE2) + (d2.x - 2 * MUL(MUL(dx, dz), ratioE));

    a2y = a2.y;
    coef4 = termB - termA - a2y;
    ay = a.y;
    cy = c.y;
    coef3 = termBD - termAC - 2 * MUL(cy, ay);
    c2y = c2.y;
    coef2 = termD + (SQ(radiusA) - SQ(radiusB) - termC) - c2y;
    crossTerm = 2 * MUL(cy, ay);
    restB = SQ(radiusB) - termD;

    denom = MulFx64ByFx32_02049690((s64)coef4 << 20, coef4) - (MulFx64ByFx32_02049690((s64)a2y << 20, -termB) << 2);
    negB = -termB;
    negBD = -termBD;
    k3 = 2 * MUL(coef4, coef3) - 4 * (MUL(a2y, negBD) + MUL(crossTerm, negB));
    k2 = SQ(coef3) + 2 * MUL(coef4, coef2) - 4 * (MUL(c2y, negB) + (MUL(a2y, restB) + MUL(crossTerm, negBD)));
    k1 = 2 * MUL(coef3, coef2) - 4 * (MUL(crossTerm, restB) + MUL(c2y, negBD));
    k0 = SQ(coef2) - 4 * MUL(c2y, restB);

    func_0204c6c0(DivFx64Shifted_020496b4(k3, denom), DivFx64Shifted_020496b4(k2, denom),
                  DivFx64Shifted_020496b4(k1, denom), DivFx64Shifted_020496b4(k0, denom), roots);
    result = MinOfArray_020496d8(12, roots);
    if (result != 0x7fffffff) {
        fx32 along;

        point = VecMultAdd(result, velocity, &diff);
        along = VEC_DotProduct_01ff9e6c(&point, &basisA.row[1]) -
                FX_Div_01ff9c84(MUL(VEC_DotProduct_01ff9e6c(&point, &basisA.row[0]), fx), fz);
        func_02048b30(&contact, &basisA.row[1], along);
        MultAddOut_02048c48(&contact,
                            SignOf_02048ad8(VEC_DotProduct_01ff9e6c(&point, &axis)) *
                                FX_Sqrt_01ff9cfc(SQ(radiusA) - SQ(along)),
                            &axis, &contact);
        SubtractVecFx32Out_02047d2c(&offset, &contact, &point);
        armA = VecCross(&contact, &capA->dir);
        armB = VecCross(&offset, &capB->dir);
        *outNormal = VecOp(&armA, &armB);
        VEC_NormalizeUnchecked_01ff9f88(outNormal, outNormal);
    }
    }
    return result;
}
