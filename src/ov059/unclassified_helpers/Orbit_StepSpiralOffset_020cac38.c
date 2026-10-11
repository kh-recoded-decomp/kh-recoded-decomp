#pragma opt_common_subs off
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SpiralMotion {
    fx32 elapsed;
    fx32 angle;
} SpiralMotion;

extern const s16 g_sinTable_0205356c[];
extern fx32 EaseProgress_0204a174(fx32 elapsed, fx32 duration, int mode);
extern int FixedPointMultiply12(int left, int right);

void Orbit_StepSpiralOffset_020cac38(SpiralMotion *motion, VecFx32 *out) {
    fx64 angle;
    fx64 progress;
    fx64 rest;
    fx32 blended;
    int index;
    fx32 radius;

    motion->elapsed += FX32_ONE;
    progress = EaseProgress_0204a174(motion->elapsed, 0x1b000, 3);
    rest = FX32_ONE - (fx32)progress;
    angle = motion->angle;
    blended = (fx32)(((fx32)angle * rest + 0x800LL) >> 12) + (fx32)(((fx32)angle * progress + 0x800LL) >> 12);
    index = (fx32)((((s64)blended << 16) / 0x6488) & 0xffff) >> 4;
    radius = (fx32)((rest * 0x800 + 0x800LL) >> 12) + (fx32)((progress * 0xa000 + 0x800LL) >> 12);
    out->x = FixedPointMultiply12(g_sinTable_0205356c[(0x400 - index) & 0xfff], radius);
    out->z = FixedPointMultiply12(g_sinTable_0205356c[index], radius);
    out->y = 0;
}
