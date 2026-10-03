#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LandingEntry {
    u8 pad_00[0x38];
    VecFx32 target;
} LandingEntry;

typedef struct HeightInfo {
    u8 pad_00[4];
    fx32 height;
} HeightInfo;

extern VecFx32 *func_ov001_0206dc4c(int index);
extern HeightInfo *func_ov042_020bd290(void);
extern fx32 func_ov042_020bd584(void);
extern void DispatchListHeadCallback_020a4100(LandingEntry *entry);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void SolveMonicQuadratic_0204c17c(fx32 linear, fx32 constant, fx32 *rootHigh, fx32 *rootLow);
extern fx32 func_02006450(fx32 left, fx32 right);

void AimEntryLandingPoint_020a5048(VecFx32 *velocity, LandingEntry *entry)
{
    VecFx32 *origin = func_ov001_0206dc4c(0);
    HeightInfo *info = func_ov042_020bd290();
    fx32 offset = func_ov042_020bd584();
    fx32 time;
    fx32 roots[2];

    DispatchListHeadCallback_020a4100(entry);
    entry->target.y = info->height + offset + 0x1c00;
    if (entry->target.y < origin->y + 0x1000) {
        entry->target.y = origin->y + 0x1000;
    }
    time = FX_Div_01ff9c84(velocity->y, -0x40);
    SolveMonicQuadratic_0204c17c(time, FX_Div_01ff9c84(-(origin->y - entry->target.y), -0x40), &roots[0], &roots[1]);
    time = (roots[0] >= roots[1]) ? roots[0] : roots[1];
    entry->target.x = origin->x - func_02006450(velocity->x, time);
    entry->target.z = origin->z - func_02006450(velocity->z, time);
}
