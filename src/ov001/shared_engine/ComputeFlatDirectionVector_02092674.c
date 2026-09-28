#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff9e3c(VecFx32 *dst, VecFx32 *src);
extern fx32 VEC_Mag_01ff9f28(VecFx32 *vec);
extern void func_ov001_02092634(fx32 z, VecFx32 *vec);
extern void func_01ffaff4(VecFx32 *dst, VecFx32 *src);

void ComputeFlatDirectionVector_02092674(VecFx32 *from, VecFx32 *to, VecFx32 *direction)
{
    func_01ff9e3c(to, from);
    direction->y = 0;
    if (VEC_Mag_01ff9f28(direction) == 0) {
        func_ov001_02092634(0x1000, direction);
    }
    func_01ffaff4(direction, direction);
}
