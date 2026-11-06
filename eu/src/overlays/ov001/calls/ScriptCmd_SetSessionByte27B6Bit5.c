#include "nitro/types.h"

extern u32 gFieldSessionWork;

u32 ScriptCmd_SetSessionByte27B6Bit5(void) {
    *(u8 *)(gFieldSessionWork + 0x27b6) = *(u8 *)(gFieldSessionWork + 0x27b6) | 0x20;
    return 1;
}
