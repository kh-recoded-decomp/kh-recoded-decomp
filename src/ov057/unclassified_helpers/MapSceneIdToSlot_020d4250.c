#include "nitro/types.h"

int MapSceneIdToSlot_020d4250(int id)
{
    int slot = -1;

    if (id == 5) {
        slot = 0;
    } else if (id >= 0x2d && id < 0x43) {
        slot = id - 0x2c;
    } else if (id >= 0x43 && id < 0x5f) {
        slot = id - 0x3e;
    }
    return slot;
}
