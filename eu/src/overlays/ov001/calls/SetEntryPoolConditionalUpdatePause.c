#include "nitro/types.h"

extern u32 gFieldEntryPoolManager;

void SetEntryPoolConditionalUpdatePause(int enable) {
    if (enable != 0) {
        *(u8 *)(gFieldEntryPoolManager + 5) |= 0xc0;
        return;
    }
    *(u8 *)(gFieldEntryPoolManager + 5) &= 0xbf;
}
