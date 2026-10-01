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

void func_ov059_020c9374(MotionTarget *target, void *arg1, void *arg2, s32 eventType)
{
    target->speed = 0;
    if (eventType != 12) {
        target->mode = -1;
    }
    switch (eventType) {
    case 1:
        target->elapsed = 0x333;
        break;
    case 2:
        target->mode = 0;
        target->timer = 0;
        break;
    case 3:
        target->mode = 2;
        target->timer = 0;
        break;
    case 4:
        target->position.y = 0;
        target->mode = 3;
        break;
    case 8:
        break;
    }
}
