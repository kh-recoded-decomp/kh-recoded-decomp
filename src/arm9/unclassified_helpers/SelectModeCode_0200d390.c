#include "nitro/types.h"

u32 SelectModeCode_0200d390(void *unused, int mode)
{
    if (mode == 1) {
        return 4;
    }
    return 0x102;
}
