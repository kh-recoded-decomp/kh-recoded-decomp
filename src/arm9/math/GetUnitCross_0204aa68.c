#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *vec);
extern void VEC_Normalize_01ff9f88(const VecFx32 *source, VecFx32 *dest);
extern void DivideVecByLength_0204a6ac(VecFx32 *vec, fx32 length);
extern VecFx32 GetPerpendicularVector_0204ad4c(const VecFx32 *vec);

static inline fx32 VecLength(const VecFx32 *vec, VecFx32 *scratch)
{
    *scratch = *vec;
    return VEC_Mag_01ff9f28(scratch);
}

static inline VecFx32 UnitPerpendicular(const VecFx32 *vec)
{
    VecFx32 perpendicular;
    VecFx32 normal;
    perpendicular = GetPerpendicularVector_0204ad4c(vec);
    VEC_Normalize_01ff9f88(&perpendicular, &normal);
    return normal;
}

static inline VecFx32 DividedByLength(VecFx32 vec, fx32 length)
{
    DivideVecByLength_0204a6ac(&vec, length);
    return vec;
}

VecFx32 GetUnitCross_0204aa68(const VecFx32 *vec, const VecFx32 *axis)
{
    VecFx32 check;
    VecFx32 copy;
    VecFx32 cross;
    fx32 length;

    VEC_CrossProduct_01ff9ea8(vec, axis, &cross);
    copy = cross;
    length = VecLength(&cross, &check);
    if (length < 0x10) {
        return UnitPerpendicular(vec);
    }
    return DividedByLength(copy, length);
}

