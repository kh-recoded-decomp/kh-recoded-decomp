extern char data_02056e20[];

/* NitroSDK saves registers into exception context. */
asm void OSi_SetExContext_02003da8(void)
{
    ldr r1, =data_02056e20
    str r0, [r1, #0x6c]
    ldr r0, [r12, #0]
    str r0, [r1, #4]
    ldr r0, [r12, #4]
    str r0, [r1, #8]
    ldr r0, [r12, #8]
    str r0, [r1, #12]
    ldr r0, [r12, #12]
    str r0, [r1, #16]
    ldr r2, [r12, #16]
    bic r2, r2, #1
    add r0, r1, #20
    stmia r0, {r4-r11}
    ldr r0, [r2, #0]
    str r0, [r1, #0x64]
    ldr r3, [r2, #4]
    str r3, [r1, #0]
    ldr r0, [r2, #8]
    str r0, [r1, #0x34]
    ldr r0, [r2, #12]
    str r0, [r1, #0x40]
    mrs r0, CPSR
    orr r3, r3, #0x80
    bic r3, r3, #0x20
    msr CPSR_cxsf, r3
    str sp, [r1, #0x38]
    str lr, [r1, #0x3c]
    mrs r2, SPSR
    msr CPSR_cxsf, r0
    bx lr
}
