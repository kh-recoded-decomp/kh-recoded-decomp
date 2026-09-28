#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_02053438;
extern BOOL func_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);

BOOL NormalizeUnlessDefault_0204a980(VecFx32 *vec)
{
    BOOL isDefault = func_0204a8f4(vec, &data_02053438);
    if (isDefault == 0) {
        func_01ff9f88(vec, vec);
        return 0;
    }
    return 1;
}
