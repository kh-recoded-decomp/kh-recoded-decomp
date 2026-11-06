#include "nitro/types.h"

extern u32 gFieldSessionWork;

u32 GetSessionScriptRunMask(void) {
    return (s32)*(s8 *)(gFieldSessionWork + 0x2738) & 0x81;
}
