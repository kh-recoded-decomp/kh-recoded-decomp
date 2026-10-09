/* CodeWarrior signed 64-bit remainder entry. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _ll_mod
    .type _ll_mod, %function
_ll_mod:
    push {r4, r5, r6, r7, fp, ip, lr}
    mov r4, r1
    orr r4, r4, #1
    b __ll_div_signed_entry
    .size _ll_mod, .-_ll_mod
