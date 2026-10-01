#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Segment {
    VecFx32 start;
    VecFx32 end;
} Segment;

extern void GetSegmentDirection_0203f950(VecFx32 *out, const Segment *segment);

void GetSegmentHalfDirection_02040fdc(VecFx32 *out, const Segment *segment)
{
    VecFx32 half;
    VecFx32 direction;

    GetSegmentDirection_0203f950(&direction, segment);
    half = direction;
    half.x >>= 1;
    half.y >>= 1;
    half.z >>= 1;
    *out = half;
}
