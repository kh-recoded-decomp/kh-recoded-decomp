#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_02053438;
extern BOOL func_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);

BOOL HasVelocityDeviated_020321d4(VecFx32 *velocity, VecFx32 *original)
{
    VecFx32 delta;
    VecFx32 originalDir;
    VecFx32 deltaDir;
    VecFx32 difference;
    VecFx32 originalUnit;
    VecFx32 deltaUnit;
    fx32 originalMag;

    if (!func_0204a8f4(velocity, &data_02053438)) {
        VEC_Subtract_01ff9e3c(velocity, original, &difference);
        delta = difference;
        if (!func_0204a8f4(&delta, &data_02053438)) {
            func_01ff9f88(&delta, &deltaUnit);
            deltaDir = deltaUnit;
            originalMag = func_01ffaff4(original, &originalUnit);
            originalDir = originalUnit;
            if (VEC_DotProduct_01ff9e6c(&originalDir, &deltaDir) < 0xff0 || originalMag < VEC_Mag_01ff9f28(velocity)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
