#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff8830(void *dest, u32 value, u32 size);

typedef struct {
    s32 id;
    s32 count;
    s32 param;
    VecFx32 start;
    VecFx32 end;
    u32 pad_024;
} PathSegment;

void InitPathSegment_020ac104(PathSegment *segment, s32 id, s32 count, s32 param, const VecFx32 *start, const VecFx32 *end)
{
    func_01ff8830(segment, 0, sizeof(PathSegment));
    if (count < 0) {
        count = 0;
    }
    segment->id = id;
    segment->count = count;
    segment->param = param;
    if (start != NULL) {
        segment->start = *start;
    }
    if (end != NULL) {
        segment->end = *end;
    }
}
