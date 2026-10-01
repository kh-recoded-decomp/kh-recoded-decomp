#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void DivideVecByLength_0204a6ac(VecFx32 *v, fx32 length);
extern void func_0204a5e4(VecFx32 *v, fx32 scale);

BOOL ClampVecLength_0204ac28(VecFx32 *vec, fx32 maxLength)
{
    fx32 length = VEC_Mag_01ff9f28(vec);

    if (length <= maxLength) {
        return FALSE;
    }
    DivideVecByLength_0204a6ac(vec, length);
    func_0204a5e4(vec, maxLength);
    return TRUE;
}
