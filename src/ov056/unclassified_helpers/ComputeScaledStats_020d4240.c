#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 primary;
    s32 secondary;
    u8 pad_08[4];
    s32 tertiary;
    u8 isValid;
} ScaledStats;

typedef struct {
    u8 pad_000[0x178];
    s32 basePrimary;
    s32 baseSecondary;
    s32 baseTertiary;
} StatSource;

extern s32 FixedPointMultiply12(s32 left, s32 right);
extern s32 func_02023dbc(s32 numerator, s32 denominator);

void ComputeScaledStats_020d4240(StatSource *source, ScaledStats *stats, s32 percent, u8 flags, fx32 scale)
{
    s32 primary;
    s32 tertiary;
    s32 secondary;

    stats->isValid = TRUE;
    primary = source->basePrimary;
    stats->primary = primary;
    stats->primary += func_02023dbc(FixedPointMultiply12(scale, primary * percent), 100);
    tertiary = source->baseTertiary;
    stats->tertiary = tertiary + func_02023dbc(tertiary * percent, 100);
    secondary = source->baseSecondary;
    stats->secondary = secondary;
    if (flags & 1) {
        stats->secondary += func_02023dbc(secondary * percent, 100);
    }
}
