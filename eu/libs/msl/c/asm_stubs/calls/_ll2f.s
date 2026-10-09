/* CodeWarrior signed 64-bit integer to float conversion. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _ll2f
    .type _ll2f, %function
_ll2f:
    ands r2, r1, #0x80000000
    beq .L_positive
    rsbs r0, r0, #0
    rsc r1, r1, #0
.L_positive:
    cmp r1, #0
    bne .L_wide
    movs r0, r0
    b _fflt + 12
.L_wide:
    clz r3, r1
    movs r1, r1, lsl r3
    rsb r3, r3, #0x20
    orr r1, r1, r0, lsr r3
    rsb ip, r3, #0x20
    movs r0, r0, lsl ip
    orrne r1, r1, #1
    add r3, r3, #0x9e
    ands ip, r1, #0xff
    add r0, r1, r1
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bxeq lr
    tst ip, #0x80
    bxeq lr
    ands r3, ip, #0x7f
    andeqs r3, r0, #1
    addne r0, r0, #1
    bx lr
    .size _ll2f, .-_ll2f
