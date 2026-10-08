typedef unsigned int u32;

/* NitroSDK cache flush by address range. */
asm void DC_FlushRange_0200344c(register const void *startAddr, register u32 nBytes)
{
    mov r12, #0
    add r1, r1, r0
    bic r0, r0, #31
@1:
    mcr p15, 0, r12, c7, c10, 4
    mcr p15, 0, r0, c7, c14, 1
    add r0, r0, #32
    cmp r0, r1
    blt @1
    bx lr
}
