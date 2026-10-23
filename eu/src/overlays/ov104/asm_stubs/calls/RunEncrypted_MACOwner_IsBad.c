#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

asm u32 RunEncrypted_MACOwner_IsBad(void)
{
    orr    ip, pc, pc
    ands   ip, ip, ip
    moveq  ip, #0
    addne  ip, ip, #0x1c
    ldr    ip, [ip, #0x14]
    sub    ip, ip, #0x1000
    stmfd  sp!, {ip}
    orr    ip, pc, pc
    ldmfd  sp!, {pc}
}
