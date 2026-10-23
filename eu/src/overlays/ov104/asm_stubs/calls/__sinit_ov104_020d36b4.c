#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

asm void __sinit_ov104_020d36b4(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable
}
