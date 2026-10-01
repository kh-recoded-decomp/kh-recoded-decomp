#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactPoint {
    u32 unk_00;
    VecFx32 normal;
} ContactPoint;

typedef struct ContactShape {
    u8 pad_00[0x20];
    VecFx32 direction;
} ContactShape;

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

int CheckFacingAway_0208350c(void *context, ContactPoint *point, int *result, ContactShape *shape)
{
    if (VEC_DotProduct_01ff9e6c(&point->normal, &shape->direction) >= 0) {
        return 0;
    }
    *result = 1;
    return 2;
}
