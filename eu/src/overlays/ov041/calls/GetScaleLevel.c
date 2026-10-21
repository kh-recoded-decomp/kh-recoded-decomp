#include "nitro/types.h"
#include "nitro/fx.h"

extern const fx32 gStageOrbValues[3];

/* Which of the three levels (thresholds 1, 2 and 4) a value falls in: 0, 1 or 2. */
int GetScaleLevel(fx32 value)
{
    u32 level;

    for (level = 1; level < 3; level++) {
        if (value <= gStageOrbValues[level]) {
            return level - 1;
        }
    }
    return level - 1;
}
