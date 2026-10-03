#include "nitro/types.h"

typedef struct {
    int pad0;
    int target;
    int current;
    int step;
    u8 pad10[0xe];
    u16 counter;
} ApproachValue;

extern int FixedPointMultiply12(int left, int right);

int ApproachTargetValue_020d0e80(ApproachValue *value)
{
    int current;
    int target;
    value->counter = 0;
    current = value->current;
    target = value->target;
    if (target >= current) {
        value->current = current + value->step;
        if (target < value->current) {
            value->current = target;
        }
    } else {
        value->current = FixedPointMultiply12(current, 0xccd);
        if (value->current < value->target) {
            value->current = value->target;
        }
    }
    if (value->current < 0) {
        value->current = 0;
    }
    return value->current;
}
