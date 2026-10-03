#include "nitro/types.h"

extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);

void InitPanelMotionB_020d0050(int *params)
{
    params[0] = random_next_scaled_0202aa04(2) ? 0 : 0x3244;
    params[1] = 0x666;
    params[2] = 0x666;
    params[3] = 0;
    params[4] = 0x14000;
}
