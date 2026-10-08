/* Runtime double greater-than compare helper. */
asm int _dgr_0202367c(double left, double right)
{
    mov r12, #0x200000
    cmn r12, r1, lsl #1
    bhs @left_special
    cmn r12, r3, lsl #1
    bhs @right_special
@compare:
    orrs r12, r3, r1
    bmi @negative
    cmp r1, r3
    cmpeq r0, r2
    movhi r0, #1
    movls r0, #0
    bx lr
@unordered:
    mov r0, #0
    mrs r12, CPSR
    bic r12, r12, #0x20000000
    msr CPSR_f, r12
    bx lr
@negative:
    orr r12, r0, r12, lsl #1
    orrs r12, r12, r2
    moveq r0, #0
    mrs r12, CPSR
    bic r12, r12, #0x20000000
    msr CPSR_f, r12
    bxeq lr
    cmp r3, r1
    cmpeq r2, r0
    movhi r0, #1
    movls r0, #0
    bx lr
@left_special:
    bne @unordered
    cmp r0, #0
    bhi @unordered
    cmn r12, r3, lsl #1
    blo @compare
@right_special:
    bne @unordered
    cmp r2, #0
    bhi @unordered
    b @compare
}
