#include "nitro/types.h"

extern u32 gFieldSessionWork;

s32 GetFieldSessionState(void) {
    return (s32)*(s8 *)(gFieldSessionWork + 0x2808);
}
