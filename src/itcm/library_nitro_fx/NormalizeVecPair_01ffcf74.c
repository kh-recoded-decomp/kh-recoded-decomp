

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/hw.h"

void NormalizeVecPair_01ffcf74(VecFx32 *first, VecFx32 *second)
{
    s64 firstSquared = (s64)first->x * first->x + (s64)first->y * first->y;
    s64 firstScale;
    fx32 firstMagnitude;
    s64 secondSquared;
    fx32 secondMagnitude;
    s64 secondScale;

    firstSquared += (s64)first->z * first->z;

    REG_DIVCNT = 2;
    REG_DIV_NUMER = 0x0100000000000000ULL;
    REG_DIV_DENOM = firstSquared;
    REG_SQRTCNT = 1;
    REG_SQRT_PARAM = (u64)(firstSquared * 4);

    secondSquared = (s64)second->x * second->x + (s64)second->y * second->y;
    secondSquared += (s64)second->z * second->z;

    while (REG_SQRTCNT & 0x8000) {
    }
    firstMagnitude = (fx32)REG_SQRT_RESULT;
    REG_SQRTCNT = 1;
    REG_SQRT_PARAM = (u64)(secondSquared * 4);

    while (REG_DIVCNT & 0x8000) {
    }
    firstScale = *(s64 *)REG_DIV_RESULT_ADDR;

    REG_DIVCNT = 2;
    REG_DIV_NUMER = 0x0100000000000000ULL;
    firstScale *= firstMagnitude;
    *(s64 *)REG_DIV_DENOM_ADDR = secondSquared;

    first->x = (fx32)((firstScale * first->x + (1LL << 44)) >> 45);
    first->y = (fx32)((firstScale * first->y + (1LL << 44)) >> 45);
    first->z = (fx32)((firstScale * first->z + (1LL << 44)) >> 45);

    while (REG_SQRTCNT & 0x8000) {
    }
    secondMagnitude = (fx32)REG_SQRT_RESULT;
    while (REG_DIVCNT & 0x8000) {
    }
    secondScale = REG_DIV_RESULT;
    secondScale *= secondMagnitude;

    second->x = (fx32)((secondScale * second->x + (1LL << 44)) >> 45);
    second->y = (fx32)((secondScale * second->y + (1LL << 44)) >> 45);
    second->z = (fx32)((secondScale * second->z + (1LL << 44)) >> 45);
}
