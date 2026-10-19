#pragma opt_propagation on
#pragma opt_common_subs off
#include "src/overlays/ov015/WirelessMenuContext.h"

#define FX32_SHIFT 12
#define FX32_ONE 0x1000
#define FX32_HALF 0x800
#define FX32_PI 0x3244

typedef struct SubBackgroundScrollRegisters {
    volatile u32 bg0;
    volatile u32 bg1;
    volatile u32 bg2;
} SubBackgroundScrollRegisters;

extern WirelessMenuContext *data_ov015_0207e960;
extern const s16 gSinFx12Table[4096];

static inline fx32 DegreesToFixed(s32 degrees)
{
    float rounded;
    if (degrees > 0) {
        rounded = degrees * FX32_ONE + 0.5f;
    } else {
        rounded = degrees * FX32_ONE - 0.5f;
    }
    return (fx32)rounded;
}

void AnimateWirelessBackgroundScroll(void)
{
    s32 degrees;
    fx32 fixedDegrees;
    s64 radians;
    s32 angleIndex;
    fx32 cosine;
    s32 offset;
    SubBackgroundScrollRegisters *registers =
        (SubBackgroundScrollRegisters *)0x04001010;

    data_ov015_0207e960->phaseDegrees += 4;
    data_ov015_0207e960->phaseDegrees %= 360;
    degrees = data_ov015_0207e960->phaseDegrees;
    fixedDegrees = DegreesToFixed(degrees);
    radians = (s64)fixedDegrees * FX32_PI / (180 * FX32_ONE);
    angleIndex = (radians * 0x10000 / (2 * FX32_PI)) & 0xffff;
    cosine = gSinFx12Table[(0x400 - (angleIndex >> 4)) & 0xfff];
    offset = (s32)(((s64)cosine * 2 + FX32_HALF) >> FX32_SHIFT);
    registers->bg0 = ((u32)(offset + 2) << 16) & 0x01ff0000;
    registers->bg2 = ((u32)(-2 - offset) << 16) & 0x01ff0000;
}
