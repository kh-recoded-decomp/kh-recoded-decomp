extern char data_02056b6c[];
extern char data_027e00a0[];
extern void CP_SaveContext_0200a15c(void);
extern void CPi_RestoreContext_0200a19c(void);

/* NitroSDK IRQ return path with thread switch. */
asm void OS_IrqHandler_ThreadSwitch_01ff81b0(void)
{
    ldr r12, =data_027e00a0
    mov r3, #0
    ldr r12, [r12]
    mov r2, #1
    cmp r12, #0
    beq @L050
@L018:
    str r2, [r12, #0x64]
    str r3, [r12, #0x78]
    str r3, [r12, #0x7c]
    ldr r0, [r12, #0x80]
    str r3, [r12, #0x80]
    mov r12, r0
    cmp r12, #0
    bne @L018
    ldr r12, =data_027e00a0
    str r3, [r12]
    str r3, [r12, #4]
    ldr r12, =data_02056b6c
    mov r1, #1
    strh r1, [r12]
@L050:
    ldr r12, =data_02056b6c
    ldrh r1, [r12]
    cmp r1, #0
    ldreq pc, [sp], #4
    mov r1, #0
    strh r1, [r12]
    mov r3, #0xd2
    msr CPSR_c, r3
    add r2, r12, #8
    ldr r1, [r2]
@L078:
    cmp r1, #0
    ldrneh r0, [r1, #0x64]
    cmpne r0, #1
    ldrne r1, [r1, #0x68]
    bne @L078
    cmp r1, #0
    bne @L0a0
@L094:
    mov r3, #0x92
    msr CPSR_c, r3
    ldr pc, [sp], #4
@L0a0:
    ldr r0, [r12, #4]
    cmp r1, r0
    beq @L094
    ldr r3, [r12, #0xc]
    cmp r3, #0
    beq @L0c8
    stmfd sp!, {r0, r1, r12}
    mov lr, pc
    bx r3
    ldmfd sp!, {r0, r1, r12}
@L0c8:
    str r1, [r12, #4]
    mrs r2, spsr
    str r2, [r0, #0]!
    stmfd sp!, {r0, r1}
    add r0, r0, #0
    add r0, r0, #0x48
    ldr r1, =CP_SaveContext_0200a15c
    blx r1
    ldmfd sp!, {r0, r1}
    ldmib sp!, {r2, r3}
    stmib r0!, {r2, r3}
    ldmib sp!, {r2, r3, r12, lr}
    stmib r0, {r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr} ^
    add r0, r0, #0x34
    stmib r0!, {lr}
    mov r3, #0xd3
    msr CPSR_c, r3
    stmib r0!, {sp}
    stmdb sp!, {r1}
    add r0, r1, #0
    add r0, r0, #0x48
    ldr r1, =CPi_RestoreContext_0200a19c
    blx r1
    ldmia sp!, {r1}
    ldr sp, [r1, #0x44]
    mov r3, #0xd2
    msr CPSR_c, r3
    ldr r2, [r1, #0]!
    msr SPSR_fc, r2
    ldr lr, [r1, #0x40]
    ldmib r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr} ^
    mov r0, r0
    stmda sp!, {r0, r1, r2, r3, r12, lr}
    ldmia sp!, {pc}
}
