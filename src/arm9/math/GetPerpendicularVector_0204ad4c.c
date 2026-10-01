#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 PickPerpendicularAxis_0204acb0(const VecFx32 *vec);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline VecFx32 Cross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct_01ff9ea8(a, b, &result);
    return result;
}

static inline VecFx32 CrossWithAxis(const VecFx32 *vec)
{
    VecFx32 axis;

    axis = PickPerpendicularAxis_0204acb0(vec);
    return Cross(vec, &axis);
}

VecFx32 GetPerpendicularVector_0204ad4c(const VecFx32 *vec)
{
    if (vec->x == 0 && vec->y == 0 && vec->z == 0) {
        VecFx32 fallback = PickPerpendicularAxis_0204acb0(vec);
        return CrossWithAxis(&fallback);
    }
    return CrossWithAxis(vec);
}
