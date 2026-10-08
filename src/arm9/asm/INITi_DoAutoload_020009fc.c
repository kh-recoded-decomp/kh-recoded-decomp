extern void func_02000a74(void);

/* NitroSDK crt0 do_autoload section copier. */
asm void INITi_DoAutoload_020009fc(void)
{
    ldr r0, =0x02000b88
    ldr r1, [r0, #0]
    ldr r2, [r0, #4]
    ldr r3, [r0, #8]
@next_block:
    cmp r1, r2
    beq @skipout
    ldr r5, [r1], #4
    ldr r7, [r1], #4
    add r6, r5, r7
    mov r4, r5
@copy:
    cmp r4, r6
    ldrmi r7, [r3], #4
    strmi r7, [r4], #4
    bmi @copy
    ldr r7, [r1], #4
    add r6, r4, r7
    mov r7, #0
@clear:
    cmp r4, r6
    strcc r7, [r4], #4
    bcc @clear
    bic r4, r5, #0x1f
@cacheflush:
    mcr p15, 0, r7, c7, c10, 4
    mcr p15, 0, r4, c7, c5, 1
    mcr p15, 0, r4, c7, c14, 1
    add r4, r4, #0x20
    cmp r4, r6
    blt @cacheflush
    b @next_block
@skipout:
    b func_02000a74
}
