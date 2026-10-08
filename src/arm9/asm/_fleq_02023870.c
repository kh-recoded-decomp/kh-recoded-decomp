/* Runtime float less-or-equal compare helper. */
asm int _fleq_02023870(float left, float right)
{
    mov r3, #0xff000000
    cmp r3, r0, lsl #1
    cmphs r3, r1, lsl #1
    blo @unordered
    cmp r0, #0
    bicmi r0, r0, #0x80000000
    rsbmi r0, r0, #0
    cmp r1, #0
    bicmi r1, r1, #0x80000000
    rsbmi r1, r1, #0
    cmp r0, r1
    movle r0, #1
    movgt r0, #0
    mrs r12, CPSR
    orrgt r12, r12, #0x20000000
    bicgt r12, r12, #0x40000000
    bicle r12, r12, #0x20000000
    orrle r12, r12, #0x40000000
    msr CPSR_f, r12
    bx lr
@unordered:
    mov r0, #0
    mrs r12, CPSR
    bic r12, r12, #0x40000000
    orr r12, r12, #0x20000000
    msr CPSR_f, r12
    bx lr
}
