/* Runtime float equality compare helper. */
asm int _feq_02023934(float left, float right)
{
    mov r3, #0xff000000
    cmp r3, r0, lsl #1
    blo @unordered
    cmp r3, r1, lsl #1
    blo @unordered
    orr r3, r0, r1
    movs r3, r3, lsl #1
    moveq r0, #1
    bne @compare
    mrs r12, CPSR
    orr r12, r12, #0x40000000
    msr CPSR_f, r12
    bx lr
@compare:
    cmp r0, r1
    moveq r0, #1
    movne r0, #0
    mrs r12, CPSR
    orreq r12, r12, #0x40000000
    bicne r12, r12, #0x40000000
    msr CPSR_f, r12
    bx lr
@unordered:
    mov r0, #0
    mrs r12, CPSR
    bic r12, r12, #0x40000000
    msr CPSR_f, r12
    bx lr
}
