#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x13];
    u8 scaleMask : 5;
} ChannelScaler;

extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

void ScaleMaskedChannels_020aa5b8(ChannelScaler *scaler, VecFx32 *vec, fx32 *single, fx32 *balance, int rawScale)
{
    fx32 scale = (s16)rawScale;
    fx32 value;

    if (scaler->scaleMask & 1) {
        vec->x = FixedPointMultiply12(vec->x, scale);
    }
    if (scaler->scaleMask & 2) {
        vec->y = FixedPointMultiply12(vec->y, scale);
    }
    if (scaler->scaleMask & 4) {
        vec->z = FixedPointMultiply12(vec->z, scale);
    }
    if (scaler->scaleMask & 8) {
        *single = FixedPointMultiply12(*single, scale);
    }
    if (scaler->scaleMask & 0x10) {
        value = FixedPointMultiply12(*balance + 0x1000, scale) - 0x1000;
        if (value < -0x1000) {
            value = -0x1000;
        }
        if (value > 0x1000) {
            value = 0x1000;
        }
        *balance = value;
    }
}
