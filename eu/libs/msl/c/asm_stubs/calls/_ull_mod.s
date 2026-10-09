/* CodeWarrior unsigned 64-bit remainder entry. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _ull_mod
    .type _ull_mod, %function
_ull_mod:
    push {r4, r5, r6, r7, fp, ip, lr}
    mov r4, #1
    .global __ull_div_common
__ull_div_common:
    orrs r5, r3, r2
    bne .L_divisor_nonzero
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_divisor_nonzero:
    orrs r5, r1, r3
    bne __ll_div_magnitude_common
    mov r1, r2
    bl _u32_div_not_0_f
    cmp r4, #0
    movne r0, r1
    mov r1, #0
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
    .size _ull_mod, .-_ull_mod
