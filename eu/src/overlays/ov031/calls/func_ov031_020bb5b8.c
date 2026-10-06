#include "nitro/types.h"

u32 func_ov031_020bb5b8(u32 unused, int *entry)
{
    if ((entry != 0) && (entry[1] == 2) && (((int *)entry[0])[1] != 2)) {
        ((int *)entry[0])[2] = 1;
        return 2;
    }
    return 1;
}
