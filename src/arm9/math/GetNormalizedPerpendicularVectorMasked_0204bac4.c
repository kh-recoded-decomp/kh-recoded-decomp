#include "nitro/types.h"
#include "nitro/fx_types.h"

/* Explicit result-pointer form of the ARM aggregate-return ABI. */
extern void PickPerpendicularAxis_0204acb0(VecFx32 *out, const VecFx32 *vector);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 NormalizeOrVerticalAxis_0204b8bc(const VecFx32 *source, VecFx32 *out, BOOL vertical);

static inline BOOL IsZeroForMode(const VecFx32 *vector, BOOL vertical)
{
    if (vertical) {
        return vector->y == 0;
    }
    return vector->x == 0 && vector->y == 0 && vector->z == 0;
}

static inline fx32 MultiplyFx32(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

VecFx32 GetNormalizedPerpendicularVectorMasked_0204bac4(const VecFx32 *vector, s32 skipHorizontal)
{
    VecFx32 normal;
    VecFx32 normalized;
    VecFx32 cross;
    VecFx32 chosenAxis;
    VecFx32 unitAxis;
    VecFx32 fallbackCross;
    VecFx32 chosenFallbackAxis;
    VecFx32 unitFallbackAxis;
    VecFx32 reference;
    VecFx32 perpendicular;
    VecFx32 initial;
    VecFx32 fallback;
    VecFx32 *normalPoint;
    VecFx32 *referencePoint;
    VecFx32 *initialPoint;

    if (IsZeroForMode(vector, skipHorizontal)) {
        if (!skipHorizontal) {
            PickPerpendicularAxis_0204acb0(&chosenFallbackAxis, vector);
            initialPoint = &initial;
            *initialPoint = chosenFallbackAxis;
        } else {
            unitFallbackAxis.x = 0x1000;
            unitFallbackAxis.y = 0;
            unitFallbackAxis.z = 0;
            initialPoint = &initial;
            *initialPoint = unitFallbackAxis;
        }
        fallback = *initialPoint;
        PickPerpendicularAxis_0204acb0(&perpendicular, &fallback);
        VEC_CrossProduct_01ff9ea8(&fallback, &perpendicular, &fallbackCross);
        normalPoint = &normal;
        *normalPoint = fallbackCross;
    } else {
        if (!skipHorizontal) {
            PickPerpendicularAxis_0204acb0(&chosenAxis, vector);
            referencePoint = &reference;
            *referencePoint = chosenAxis;
        } else {
            unitAxis.x = 0x1000;
            unitAxis.y = 0;
            unitAxis.z = 0;
            referencePoint = &reference;
            *referencePoint = unitAxis;
        }
        if (!skipHorizontal) {
            VEC_CrossProduct_01ff9ea8(vector, referencePoint, &cross);
        } else {
            cross.x = -MultiplyFx32(vector->z, referencePoint->y);
            cross.y = 0;
            cross.z = MultiplyFx32(vector->x, referencePoint->y);
        }
        normalPoint = &normal;
        *normalPoint = cross;
    }
    NormalizeOrVerticalAxis_0204b8bc(normalPoint, &normalized, skipHorizontal);
    return normalized;
}
