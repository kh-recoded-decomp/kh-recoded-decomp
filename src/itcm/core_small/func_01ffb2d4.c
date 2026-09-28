#include "nitro/types.h"

#define FLAG_OVERRIDE 4

/* Indexed slot lookup with slot-0 override */
u32 func_01ffb2d4(u16 *record, int index)
{
    if (((*record & FLAG_OVERRIDE) != 0) && (index == 0)) {
        return *(u32 *)(record + 0x66);
    }
    return *(u32 *)(record + index * 2 + 6);
}
