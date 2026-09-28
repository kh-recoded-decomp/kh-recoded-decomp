#include "nitro/types.h"

u32
func_ov001_020825a0(u32 unused, int *record)
{
    if ((record != (int *)0x0) && (record[1] == 2) && (*(int *)(*record + 4) == 0)) {
        return 1;
    }
    return 0;
}
