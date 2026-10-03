#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 data_02053438;
extern int random_next_scaled_0202aa04(int range);
extern int nextRandom12_0202aa58(void);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

void RandomScaledDirection_020b0488(fx32 scale, VecFx32 *dir)
{
    random_next_scaled_0202aa04(0xffff);
    random_next_scaled_0202aa04(0xffff);
    random_next_scaled_0202aa04(0xffff);
    dir->x = nextRandom12_0202aa58() - 0x800;
    dir->y = nextRandom12_0202aa58() - 0x800;
    dir->z = nextRandom12_0202aa58() - 0x800;
    if (VEC_Mag_01ff9f28(dir) >= 0) {
        VEC_Normalize_01ff9f88(dir, dir);
    } else {
        *dir = data_02053438;
    }
    dir->x = FixedPointMultiply12(dir->x, scale);
    dir->y = FixedPointMultiply12(dir->z, scale);
    dir->z = FixedPointMultiply12(dir->z, scale);
}
