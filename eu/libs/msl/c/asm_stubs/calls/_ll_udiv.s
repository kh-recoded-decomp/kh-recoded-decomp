/* CodeWarrior unsigned 64-bit division entry. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _ll_udiv
    .type _ll_udiv, %function
_ll_udiv:
    push {r4, r5, r6, r7, fp, ip, lr}
    mov r4, #0
    b __ull_div_common
    .size _ll_udiv, .-_ll_udiv
