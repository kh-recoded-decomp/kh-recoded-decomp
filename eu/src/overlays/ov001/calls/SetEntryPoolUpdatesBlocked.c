#include "nitro/types.h"

extern u32 gFieldEntryPoolManager;

void SetEntryPoolUpdatesBlocked(int enable) {
    if (enable != 0) {
        *(u8 *)(gFieldEntryPoolManager + 5) |= 0x81;
        return;
    }
    *(u8 *)(gFieldEntryPoolManager + 5) &= 0xfe;
}
