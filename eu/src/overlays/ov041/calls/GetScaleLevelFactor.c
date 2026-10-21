#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

extern const StageScaleFactors gStageScaleFactors;

/* The factor of a scale level (see GetScaleLevel). */
fx32 GetScaleLevelFactor(int level)
{
    StageScaleFactors factors = gStageScaleFactors;

    return factors.values[level];
}
