#include "nitro/types.h"

typedef struct {
    u8 pad00[0x18];
    u32 unused0 : 2;
    u32 finished : 1;
} Tween;

extern void SampleTweenValue_0205258c(Tween *tween_state, s32 *output_value);

BOOL UpdateTweenIsFinished_020bf3bc(Tween *tween)
{
    SampleTweenValue_0205258c(tween, NULL);
    return tween->finished;
}
