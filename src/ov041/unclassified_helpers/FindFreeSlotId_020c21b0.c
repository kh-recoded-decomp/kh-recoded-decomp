#include "nitro/types.h"

extern int func_02036810(int id);

u32 FindFreeSlotId_020c21b0(void) {
    int inUse;
    u32 id;

    id = 0;
    do {
        inUse = func_02036810(id & 0xffff);
        if (inUse == 0) {
            return id & 0xff;
        }
        id = id + 1;
    } while ((int)id < 0x200);
    return 0xff;
}
