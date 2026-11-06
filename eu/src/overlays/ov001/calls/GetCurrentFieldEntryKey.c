#include "nitro/types.h"

extern u32 gFieldSessionWork;

s32 GetCurrentFieldEntryKey(void) {
    return (s32)*(s16 *)(gFieldSessionWork + 0x20a);
}
