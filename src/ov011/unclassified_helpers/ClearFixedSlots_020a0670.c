#include "nitro/types.h"

extern u32 func_ov001_0206459c(u32 slotId, u32 size, u32 value);

u32 ClearFixedSlots_020a0670(void) {
    s32 index = 0;
    do {
        func_ov001_0206459c(index * 2 + 0x331f, 2, 0);
        index = index + 1;
    } while (index < 0x100);
    func_ov001_0206459c(0x3880, 0x660, 0);
    return 1;
}
