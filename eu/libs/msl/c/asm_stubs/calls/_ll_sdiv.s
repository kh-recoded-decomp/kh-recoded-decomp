/* CodeWarrior signed 64-bit division implementation. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _ll_sdiv
    .type _ll_sdiv, %function
_ll_sdiv:
    push {r4, r5, r6, r7, fp, ip, lr}
    eor r4, r1, r3
    asr r4, r4, #1
    lsl r4, r4, #1
    .global __ll_div_signed_entry
__ll_div_signed_entry:
    orrs r5, r3, r2
    bne .L_divisor_nonzero
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_divisor_nonzero:
    lsr r5, r0, #0x1f
    add r5, r5, r1
    lsr r6, r2, #0x1f
    add r6, r6, r3
    orrs r6, r5, r6
    bne .L_wide_division
    mov r1, r2
    bl _s32_div_f
    ands r4, r4, #1
    movne r0, r1
    asr r1, r0, #0x1f
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_wide_division:
    cmp r1, #0
    bge .L_dividend_positive
    rsbs r0, r0, #0
    rsc r1, r1, #0
.L_dividend_positive:
    cmp r3, #0
    bge .L_divisor_positive
    rsbs r2, r2, #0
    rsc r3, r3, #0
    .global __ll_div_magnitude_common
__ll_div_magnitude_common:
.L_divisor_positive:
    orrs r5, r1, r0
    beq .L_zero_dividend
    mov r5, #0
    mov r6, #1
    cmp r3, #0
    bmi .L_divisor_normalized
.L_shift_divisor:
    add r5, r5, #1
    adds r2, r2, r2
    adcs r3, r3, r3
    bpl .L_shift_divisor
    add r6, r6, r5
.L_divisor_normalized:
    cmp r1, #0
    blt .L_dividend_normalized
.L_shift_dividend:
    cmp r6, #1
    beq .L_dividend_normalized
    sub r6, r6, #1
    adds r0, r0, r0
    adcs r1, r1, r1
    bpl .L_shift_dividend
.L_dividend_normalized:
    mov r7, #0
    mov ip, #0
    mov fp, #0
    b .L_subtract
.L_accept_bit:
    orr ip, ip, #1
    subs r6, r6, #1
    beq .L_finish
    adds r0, r0, r0
    adcs r1, r1, r1
    adcs r7, r7, r7
.L_subtract:
    subs r0, r0, r2
    sbcs r1, r1, r3
    sbcs r7, r7, #0
    adds ip, ip, ip
    adc fp, fp, fp
    cmp r7, #0
    bge .L_accept_bit
.L_restore:
    subs r6, r6, #1
    beq .L_restore_final
    adds r0, r0, r0
    adcs r1, r1, r1
    adc r7, r7, r7
    adds r0, r0, r2
    adcs r1, r1, r3
    adc r7, r7, #0
    adds ip, ip, ip
    adc fp, fp, fp
    cmp r7, #0
    bge .L_accept_bit
    b .L_restore
.L_restore_final:
    adds r0, r0, r2
    adc r1, r1, r3
.L_finish:
    ands r7, r4, #1
    moveq r0, ip
    moveq r1, fp
    beq .L_apply_sign
    subs r7, r5, #0x20
    lsrge r0, r1, r7
    bge .L_zero_high
    rsb r7, r5, #0x20
    lsr r0, r0, r5
    orr r0, r0, r1, lsl r7
    lsr r1, r1, r5
    b .L_apply_sign
    lsr r0, r1, r7
    mov r1, #0
.L_apply_sign:
    cmp r4, #0
    blt .L_negate
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_negate:
    rsbs r0, r0, #0
    rsc r1, r1, #0
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
.L_zero_dividend:
    mov r0, #0
.L_zero_high:
    mov r1, #0
    cmp r4, #0
    blt .L_negate
    pop {r4, r5, r6, r7, fp, ip, lr}
    bx lr
    .size _ll_sdiv, .-_ll_sdiv
