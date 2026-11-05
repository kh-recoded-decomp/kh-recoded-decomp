/* Sweep a sphere against a circular rim; EU entry 0x02047198.
 * direction is the caller's unit sweep direction. sphereRadius is the effective
 * radius supplied by the caller; sphere->radius is not read here.
 * candidateDistances must hold RIM_CANDIDATE_COUNT entries. On a miss return
 * 0x7fffffff and leave outNormal untouched. See docs/SPHERE_RIM.md for the
 * fixed-point rounding, solver ABI and porting contract.
 */
#include "src/collision/CollisionGeometry.h"

#define RIM_CANDIDATE_COUNT 12

typedef struct Basis3x3
{
    VecFx32 row[3];
} Basis3x3;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern VecFx32 PickPerpendicularAxis(const VecFx32 *vec);
extern void BuildBasisMatrix(const VecFx32 *forward, const VecFx32 *up, Basis3x3 *out);
extern void TransformVectorByBasis(const VecFx32 *vec, const Basis3x3 *rimBasis, VecFx32 *out);
extern void ApplyScalarToVec3(VecFx32 *vec, fx32 (*func)(fx32 value));
extern fx32 SquareFx32(fx32 value);
extern void MulVecFx32InPlace(VecFx32 *vec, const VecFx32 *scale);
extern void SolveQuartic(fx32 cubicCoeff, fx32 quadraticCoeff, fx32 linearCoeff, s64 constantCoeff,
                         fx32 *candidateDistances);
extern VecFx32 GetUnitRejectionFromAxis(const VecFx32 *vec, const VecFx32 *rimAxis);
extern fx32 NormalizeIfShort(VecFx32 *vec);
/* Both helpers use arithmetic right shifts. Round each FX_Mul product before summing. */
inline static fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((((fx64)a) * b) + 0x800) >> 12);
}

/* Keep all 64 shifted bits for the quartic constant; do not narrow this to fx32. */
inline static s64 MultiplyUnrounded(fx32 a, fx32 b)
{
    return (((fx64)a) * b) >> 12;
}

inline static VecFx32 SubtractVectors(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Subtract(a, b, &out);
    return out;
}

inline static Basis3x3 MakeRimBasis(const VecFx32 *forward)
{
    VecFx32 up;
    Basis3x3 out;
    up = PickPerpendicularAxis(forward);
    BuildBasisMatrix(forward, &up, &out);
    return out;
}

inline static VecFx32 TransformToBasis(const VecFx32 *vec, const Basis3x3 *rimBasis)
{
    VecFx32 out;
    TransformVectorByBasis(vec, rimBasis, &out);
    return out;
}

inline static VecFx32 RotateComponents(const VecFx32 *vec)
{
    VecFx32 out;
    out.x = vec->y;
    out.y = vec->z;
    out.z = vec->x;
    return out;
}

inline static VecFx32 SquareComponents(VecFx32 vec)
{
    ApplyScalarToVec3(&vec, SquareFx32);
    return vec;
}

inline static VecFx32 MultiplyComponents(VecFx32 vec, const VecFx32 *scale)
{
    MulVecFx32InPlace(&vec, scale);
    return vec;
}

inline static VecFx32 ScaleAndAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_MultAdd(scale, a, b, &out);
    return out;
}

inline static fx32 FindMinimum(int count, const fx32 *values)
{
    fx32 min = values[0];
    u8 i;
    for (i = 1; i < count; i++)
    {
        if (min > values[i])
        {
            min = values[i];
        }
    }

    return min;
}

inline static VecFx32 NormalizeVectorIfShort(VecFx32 vec)
{
    NormalizeIfShort(&vec);
    return vec;
}

fx32 SweepSphereAgainstRim(const CollisionSphere *sphere, const VecFx32 *direction,
                   const VecFx32 *rimCenter, fx32 rimRadius, fx32 sphereRadius,
                   const VecFx32 *rimAxis, fx32 *candidateDistances,
                   VecFx32 *outNormal)
{
    const VecFx32 centerOffset = SubtractVectors(&sphere->center, rimCenter);
    const Basis3x3 rimBasis = MakeRimBasis(rimAxis);
    const VecFx32 localDirection = TransformToBasis(direction, &rimBasis);
    const VecFx32 localOffset = TransformToBasis(&centerOffset, &rimBasis);
    /* The polynomial uses cyclic basis coordinates (y, z, x). */
    const VecFx32 rotatedDirection = RotateComponents(&localDirection);
    const VecFx32 rotatedOffset = RotateComponents(&localOffset);
    const VecFx32 directionSquares = SquareComponents(rotatedDirection);
    const VecFx32 offsetSquares = SquareComponents(rotatedOffset);
    const VecFx32 componentProducts =
        MultiplyComponents(rotatedDirection, &rotatedOffset);

    const fx32 rimRadiusSq = FX_Mul(rimRadius, rimRadius);
    const fx32 sphereRadiusSq = FX_Mul(sphereRadius, sphereRadius);
    const fx32 directionLengthSq =
        directionSquares.z + (directionSquares.x + directionSquares.y);
    const fx32 cubicCoeff =
        ((FX_Mul(componentProducts.x, directionLengthSq) +
          FX_Mul(componentProducts.y, directionLengthSq)) +
         FX_Mul(componentProducts.z, directionLengthSq)) * 4;

    fx32 productY = componentProducts.y;
    const fx32 offsetLengthSq =
        offsetSquares.z + (offsetSquares.x + offsetSquares.y);
    const fx32 offsetRadiusTerm =
        (rimRadiusSq + offsetLengthSq) - sphereRadiusSq;
    const fx32 quadraticCoeff =
        ((FX_Mul(componentProducts.z, componentProducts.z * 4) +
          ((FX_Mul(productY,
                   (productY * 4) + (componentProducts.z * 8)) +
            (FX_Mul(componentProducts.x,
                    ((componentProducts.y + componentProducts.z) * 8) +
                    (componentProducts.x * 4)) +
             (FX_Mul(directionSquares.x, offsetRadiusTerm) * 2))) +
           (FX_Mul(directionSquares.y, offsetRadiusTerm) * 2))) +
         (FX_Mul(directionSquares.z, offsetRadiusTerm) * 2)) -
        FX_Mul(rimRadiusSq * 4, directionSquares.x + directionSquares.y);

    /* Subtract each squared component from the same running remainder.
     * Keep every shifted product wide and preserve their grouping: each
     * arithmetic shift discards fractional bits before the terms are added.
     */
    fx32 remaining = offsetRadiusTerm;
    remaining -= offsetSquares.x;
    s64 constantXTerm =
        MultiplyUnrounded(offsetSquares.x,
                          offsetSquares.x + (remaining * 2));
    remaining -= offsetSquares.y;
    s64 constantYTerm =
        MultiplyUnrounded(offsetSquares.y,
                          offsetSquares.y + (remaining * 2));
    remaining -= offsetSquares.z;
    s64 constantZTerm =
        MultiplyUnrounded(offsetSquares.z,
                          offsetSquares.z + (remaining * 2));
    s64 constantCoeff =
        (constantXTerm + constantYTerm) +
        ((MultiplyUnrounded(sphereRadiusSq, sphereRadiusSq) +
          (constantZTerm +
           MultiplyUnrounded(rimRadiusSq,
                             rimRadiusSq - (sphereRadiusSq * 2)))) -
         MultiplyUnrounded(rimRadiusSq * 4,
                           offsetSquares.x + offsetSquares.y));

    const fx32 linearCoeff =
        (((FX_Mul(componentProducts.x, offsetRadiusTerm) +
           FX_Mul(componentProducts.y, offsetRadiusTerm)) +
          FX_Mul(componentProducts.z, offsetRadiusTerm)) * 4) -
        FX_Mul(rimRadiusSq * 8, componentProducts.x + productY);

    SolveQuartic(cubicCoeff, quadraticCoeff, linearCoeff,
                 constantCoeff, candidateDistances);
    const fx32 hitDistance =
        FindMinimum(RIM_CANDIDATE_COUNT, candidateDistances);

    if (hitDistance != 0x7fffffff)
    {
        const VecFx32 point =
            ScaleAndAdd(hitDistance, direction, &centerOffset);
        const VecFx32 radial = GetUnitRejectionFromAxis(&point, rimAxis);
        const VecFx32 fromRim = ScaleAndAdd(-rimRadius, &radial, &point);
        if (((fromRim.x == 0) && (fromRim.y == 0)) && (fromRim.z == 0))
        {
            *outNormal = NormalizeVectorIfShort(point);
        }
        else
        {
            *outNormal = NormalizeVectorIfShort(fromRim);
        }
    }
    return hitDistance;
}
