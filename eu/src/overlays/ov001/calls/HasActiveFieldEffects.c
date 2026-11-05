#include "nitro/types.h"

extern u32 data_ov001_020a0484;

u32 HasActiveFieldEffects(void) {
    if (*(s32 *)(data_ov001_020a0484 + 0x4c) != 0) {
        return 1;
    }
    return 0;
}
