#include "nitro/types.h"

extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);

void InitPanelMotionA_020d0020(int *params)
{
    params[0] = random_next_scaled_0202aa04(2) ? 0 : 0x3244;
    params[1] = 0x2b8;
    params[2] = 0x333;
    params[3] = 0;
    params[4] = 0xa000;
}
