#include "nitro/types.h"

u32
FilterFieldSwitchTouchContact(u32 unused, int *record)
{
    if ((record != (int *)0x0) && (record[1] == 2) && (*(int *)(*record + 4) == 0)) {
        return 1;
    }
    return 0;
}
