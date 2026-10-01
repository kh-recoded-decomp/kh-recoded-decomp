#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 func_01ffaff4(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9f88(const VecFx32 *source, VecFx32 *dest);

fx32 NormalizeIfShort_0204a9b4(VecFx32 *vec)
{
    fx32 length = func_01ffaff4(vec, vec);

    if (length < 16) {
        func_01ff9f88(vec, vec);
    }
    return length;
}
