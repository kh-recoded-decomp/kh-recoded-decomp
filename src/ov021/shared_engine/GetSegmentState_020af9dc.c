#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Segment {
    u8 pad0[0x14];
    VecFx32 end;
    VecFx32 start;
    VecFx32 extra;
} Segment;

typedef struct SegmentState {
    VecFx32 start;
    VecFx32 direction;
    VecFx32 extra;
    int angle;
} SegmentState;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern int AsinToRadians_020af980(Segment *segment);

void GetSegmentState_020af9dc(Segment *segment, SegmentState *state)
{
    VecFx32 direction;
    VecFx32 delta;
    VecFx32 temp;

    state->start = segment->start;
    VEC_Subtract_01ff9e3c(&segment->end, &segment->start, &delta);
    temp = delta;
    VEC_Normalize_01ff9f88(&temp, &direction);
    state->direction = direction;
    state->extra = segment->extra;
    state->angle = AsinToRadians_020af980(segment);
}
