#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Segment {
    VecFx32 start;
    VecFx32 end;
} Segment;

extern void GetSegmentVector_020416c8(VecFx32 *out, const Segment *segment);

void GetSegmentHalfVector_02041670(VecFx32 *out, const Segment *segment)
{
    VecFx32 half;
    VecFx32 direction;

    GetSegmentVector_020416c8(&direction, segment);
    half = direction;
    half.x >>= 1;
    half.y >>= 1;
    half.z >>= 1;
    *out = half;
}
