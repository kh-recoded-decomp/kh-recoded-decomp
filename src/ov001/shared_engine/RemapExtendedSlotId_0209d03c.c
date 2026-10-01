#include "nitro/types.h"

extern s8 data_ov001_020a036c[];

u16 RemapExtendedSlotId_0209d03c(u16 slotId)
{
    if (slotId >= 0x46) {
        s8 mapped = data_ov001_020a036c[(s8)(slotId - 0x46)];

        if (mapped < 0) {
            slotId -= 0x46;
        } else {
            slotId = mapped;
        }
    }
    return slotId;
}
