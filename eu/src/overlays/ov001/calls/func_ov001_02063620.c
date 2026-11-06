#include "nitro/types.h"

extern u32 gFieldSessionWork;

u32 func_ov001_02063620(void) {
    return (s32)*(s8 *)(gFieldSessionWork + 0x2738) & 0x81;
}
