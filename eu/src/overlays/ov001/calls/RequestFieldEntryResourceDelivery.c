#include "nitro/types.h"

extern u32 data_ov001_020a04fc;

void RequestFieldEntryResourceDelivery(void) {
    if ((*(u8 *)(data_ov001_020a04fc + 5) & 2) != 0) {
        *(u8 *)(data_ov001_020a04fc + 5) |= 0xc;
    }
}
