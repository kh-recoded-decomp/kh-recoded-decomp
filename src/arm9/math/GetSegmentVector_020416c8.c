#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Segment {
    VecFx32 start;
    VecFx32 end;
} Segment;

extern void SubtractVecFx32Into_0203f4a8(VecFx32 *dest, const VecFx32 *a, const VecFx32 *b);

void GetSegmentVector_020416c8(VecFx32 *out, const Segment *segment)
{
    VecFx32 direction;
    SubtractVecFx32Into_0203f4a8(&direction, &segment->end, &segment->start);
    *out = direction;
}
