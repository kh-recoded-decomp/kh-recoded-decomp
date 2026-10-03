#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u16 Math_AsinIdx_0202aaa8(fx32 value);

fx32 AsinToRadians_020af980(const fx32 *value) {
    return (fx32)((s64)Math_AsinIdx_0202aaa8(*value) * 0x6488 / 0x10000);
}
