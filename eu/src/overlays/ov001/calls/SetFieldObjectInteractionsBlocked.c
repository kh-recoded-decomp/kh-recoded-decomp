#include "nitro/types.h"

extern u32 gFieldEntryPoolManager;

void SetFieldObjectInteractionsBlocked(int enable) {
    if (enable != 0) {
        *(u8 *)(gFieldEntryPoolManager + 5) |= 0x20;
        return;
    }
    *(u8 *)(gFieldEntryPoolManager + 5) &= 0xdf;
}
