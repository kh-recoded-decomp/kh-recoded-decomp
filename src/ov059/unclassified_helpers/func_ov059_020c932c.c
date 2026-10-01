#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MotionTarget {
    VecFx32 position;
    VecFx32 destination;
    s32 elapsed;
    u16 speed;
    u8 pad_1E[2];
    s32 timer;
    s8 mode;
} MotionTarget;

extern const VecFx32 data_02053438;

void func_ov059_020c932c(MotionTarget *target)
{
    VecFx32 origin = data_02053438;

    target->position = origin;
    target->destination = origin;
    target->elapsed = 0;
    target->speed = 0x2000;
    target->mode = -1;
}
