#include "nitro/types.h"

asm BOOL IsSessionFlag3701Set(void)
{
    ldr r0, [pc, #4]
    ldr r3, [pc, #8]
    bx r3
    nop
    DCD 0x3701
    DCD 0x020645c9
}
