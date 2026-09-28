#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL IsPointWithinEntityRadius_02069618(int entity, const VecFx32 *point)
{
    fx32 distance;

    if ((*(u32 *)(entity + 0x18) & 0x80000000) != 0) {
        return 1;
    }
    distance = func_01ffa0f4(point, (const VecFx32 *)(entity + 0x24));
    if (distance <= *(int *)(entity + 0x18)) {
        return 1;
    }
    return 0;
}
