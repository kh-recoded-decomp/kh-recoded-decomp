#include "nitro/types.h"

extern u32 gFieldEntryPoolManager;

void RequestFieldEntryResourceDelivery(void) {
    if ((*(u8 *)(gFieldEntryPoolManager + 5) & 2) != 0) {
        *(u8 *)(gFieldEntryPoolManager + 5) |= 0xc;
    }
}
