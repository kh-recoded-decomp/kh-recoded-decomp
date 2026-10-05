#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/hw.h"

fx32 VEC_Normalize_01ffaff4(const VecFx32 *source, VecFx32 *destination) {
    s64 squaredMagnitude = (s64)source->x * source->x;
    squaredMagnitude += (s64)source->y * source->y;
    squaredMagnitude += (s64)source->z * source->z;
    fx32 magnitude;

    if (squaredMagnitude == 0) {
        destination->x = destination->y = destination->z = 0;
        return 0;
    }
    REG_DIVCNT = 2;
    REG_DIV_NUMER = 0x0100000000000000ULL;
    REG_DIV_DENOM = squaredMagnitude;
    REG_SQRTCNT = 1;
    REG_SQRT_PARAM = (u64)(squaredMagnitude * 4);

    while (REG_SQRTCNT & 0x8000) {
    }
    magnitude = (fx32)REG_SQRT_RESULT;
    while (REG_DIVCNT & 0x8000) {
    }

    squaredMagnitude = REG_DIV_RESULT;
    squaredMagnitude *= magnitude;
    destination->x = (fx32)((squaredMagnitude * source->x + (1LL << 44)) >> 45);
    destination->y = (fx32)((squaredMagnitude * source->y + (1LL << 44)) >> 45);
    destination->z = (fx32)((squaredMagnitude * source->z + (1LL << 44)) >> 45);

    return (magnitude + 1) >> 1;
}
